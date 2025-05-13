#include <vector>
#include <chrono>
#include <thread>
#include <sstream>
#include <filesystem>
#include <regex>
#include <iostream>

#include "Map.hpp"
#include "Entity.hpp"
#include "Render.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Treasure.hpp"
#include "RandomController.hpp"
#include "Sarsa.hpp"
#include "Q-Learning.hpp"
#include "FileReader.hpp"

namespace fs = std::filesystem;

void CreateEntity(Map& _map, const std::vector<std::vector<int>>& _mapGrid, std::vector<Entity*>& entities);
void Reset(Map& _map, Player* _player, std::vector<Entity*>& entities, const std::vector<std::vector<int>>& originalGrid);
std:: string SelectMap();
void Menu();
void Game();

bool running = false;

int   algorithmN = 0;

float learningRate    = 0;
float discountRate    = 0;
float epsilon         = 0;
float goalReward      = 0;
float movementReward  = 0;
float collisionReward = 0;
float killReward      = 0;
float treasureReward  = 0;
float dieReward       = 0;
float goingBackReward = 0;

int generation = 0;
int goals = 0;

std::string mapSrc;

int main() 
{

    Menu();

    Game();
}


void CreateEntity(Map& _map, const std::vector<std::vector<int>>& _mapGrid, std::vector<Entity*>& entities)
{
    std::vector<EntityStruct> entitiesStructs = FileReader::EntityCharger(_mapGrid);

    for (const auto& es : entitiesStructs)
    {
        Entity* newEntity = nullptr;

        switch (es.value)
        {
        case 4:
            newEntity = new Enemy(es.col, es.row, _map);
            break;

        case 5:
            newEntity = new Treasure(es.col, es.row, _map);
            break;

        default:
            break;
        }

        if (newEntity)
        {
            newEntity->SetActive(true);
            entities.push_back(newEntity);
        }
    }
}

void Reset(Map& _map, Player* _player, std::vector<Entity*>& entities, const std::vector<std::vector<int>>& originalGrid)
{
    // Desactivar todas las entidades menos el player
    for (Entity* entity : entities)
    {
        entity->SetActive(true);
    }

    _player->Reset();

    if (auto* sarsa = dynamic_cast<SarsaController*>(_player->GetController()))
    {
        sarsa->steps = 0;
        sarsa->firstIteration = true;
    }
    else if (auto* qLearning = dynamic_cast<QLearningController*>(_player->GetController()))
        qLearning->steps = 0;

}

std::string SelectMap()
{
    std::vector<fs::path> mapFiles;
    const fs::path folderPath = "../../../resources";
    std::regex mapPattern(R"(Map_\d+\.txt)");

    // Recoger todos los archivos válidos
    for (const auto& entry : fs::directory_iterator(folderPath))
    {
        if (entry.is_regular_file() && std::regex_match(entry.path().filename().string(), mapPattern))
        {
            mapFiles.push_back(entry.path());
        }
    }

    if (mapFiles.empty())
    {
        std::cout << "No maps found in ../../../resources" << std::endl;
        exit(1); // Puedes lanzar una excepción si prefieres
    }


    // Selección del usuario
    int choice = 0;
    while (true)
    {
        std::cout << "\033[H\033[J";
        // Mostrar lista
        std::cout << "MAZE - Q-LEARNING / SARSA\n\n";
        std::cout << "Available Maps:\n\n";
        for (size_t i = 0; i < mapFiles.size(); ++i)
        {
            std::cout << i + 1 << ": " << mapFiles[i].filename().string() << "\n";
        }

        std::cout << "\nSelect a map by number: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > static_cast<int>(mapFiles.size()))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid choice. Press Enter to try again...";
            std::cin.get();
        }
        else
        {
            break;
        }
    }

    return mapFiles[choice - 1].parent_path().string() + "/" + mapFiles[choice - 1].stem().string();
}

void Menu()
{
    mapSrc = SelectMap();

    while (algorithmN != 1 && algorithmN != 2)
    {
        std::cout << "\033[H\033[J";

        std::cout << "MAZE - Q-LEARNING / SARSA\n\n";
        std::cout << "Which algorithm do you want to use?\n\n";
        std::cout << "1: SARSA\n";
        std::cout << "2: Q-Learning\n";
        std::cout << "\nYour choice: ";

        std::cin >> algorithmN;

        if (std::cin.fail() || (algorithmN != 1 && algorithmN != 2)) 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\nInvalid input. Press Enter to continue...";

            std::cin.get();
        }
    }

    // Input for each float parameter
    auto askValue = [](const std::string& prompt, float& var, bool restrictTo01 = false)
    {
        while (true)
        {
            std::cout << "\033[H\033[J";
            std::cout << "MAZE - Q-LEARNING / SARSA\n\n";
            std::cout << prompt << ": ";
            std::cin >> var;

            if (std::cin.fail() || (restrictTo01 && (var < 0.0f || var > 1.0f)))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Invalid input";
                if (restrictTo01) std::cout << " (must be between 0 and 1)";
                std::cout << ". Press Enter to try again...";
                std::cin.get();
            }
            else
            {
                break;
            }
        }
    };

    askValue("Enter learning rate (between 0 and 1)", learningRate, true);
    askValue("Enter discount rate (between 0 and 1)", discountRate, true);
    askValue("Enter epsilon (between 0 and 1)", epsilon, true);
    askValue("Enter goal reward", goalReward);
    askValue("Enter movement reward", movementReward);
    askValue("Enter collision reward", collisionReward);
    askValue("Enter kill reward", killReward);
    askValue("Enter treasure reward", treasureReward);
    askValue("Enter die reward", dieReward);
    askValue("Enter goingBack reward", goingBackReward);
}

void Game()
{
    std::vector<std::vector<int>> mapGrid = FileReader::MapCharger(mapSrc);

    if (mapGrid.empty())
        return;

    Map map(mapGrid);

    Render render;

    std::vector<Entity*> entities;

    std::vector<Entity*> toDelete;

    std::vector<Entity*> players;

    Player player1(map);

    player1.SetActive(true);

    int maxSteps = 5000;

    // Declaramos el puntero controller de tipo Controller
    Controller* controller = nullptr;

    // Elegimos el controlador según algorithmN
    if (algorithmN == 1) // SARSA
    {
        controller = new SarsaController(learningRate, discountRate, goalReward, movementReward, collisionReward, epsilon, killReward, treasureReward, dieReward, goingBackReward, maxSteps);
    }
    else if (algorithmN == 2) // Q-Learning
    {
        controller = new QLearningController(learningRate, discountRate, goalReward, movementReward, collisionReward, epsilon, killReward, treasureReward, dieReward, goingBackReward, maxSteps);
    }
    else
    {
        return;  // Si no es ni 1 ni 2, salimos de la función
    }

    controller->LoadQTable(mapSrc);

    player1.SetController(controller);

    entities.push_back(&player1);

    CreateEntity(map, mapGrid, entities);

    running = true;

    std::ostringstream buffer;

    while (running)
    {
        buffer.str("");
        buffer.clear();

        render.RenderScene(&map, entities, buffer);

        // Limpiar solo el área de la escena (opcional)
        std::cout << "\033[H\033[J";  // Esto borra la consola

        std::cout << "Goals: " << goals << " | Generacion: " << generation << " | Pasos: " << controller->steps << " | Epsilon: " << controller->GetEpsilon() << std::endl;

        // Imprimimos el contenido de la escena
        std::cout << buffer.str();

        for (auto entiti : entities)
        {
            if(entiti->GetActive())
                entiti->Update(map, entities);
        }

        if (controller->reset)
        {
            if (player1.GetArrive())
            {
                player1.SetArrive(false);

                goals++;

                if (goals % 4 == 0 && controller->GetEpsilon() > 0.02f)
                {
                    controller->SetEpsilon(controller->GetEpsilon() * 0.9f);
                }
            }

            if (player1.GetDead())
            {
                player1.SetDead(false);
            }

            generation++;
            Reset(map, &player1, entities, mapGrid);
            controller->reset = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (generation >= 300)
            running = false;
    }

    for (auto e : entities)
    {
        if (e != &player1)
            delete e;
    }

    controller->SaveQTable(mapSrc);

    return;
}

