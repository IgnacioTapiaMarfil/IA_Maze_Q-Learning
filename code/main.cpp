
#include <vector>
#include <chrono>
#include <thread>
#include <sstream>

#include "Map.hpp"
#include "Entity.hpp"
#include "Render.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Treasure.hpp"
#include "RandomController.hpp"
#include "Sarsa.hpp"
#include "FileReader.hpp"

bool running = false;

void CreateEntity(Map& _map, std::vector<std::vector<int>> _mapGrid, std::vector<Entity*>& entities);

int generation = 0;

int goals = 0;

int main() 
{
    const std::string mapSrc = "../../../resources/Map_02";
    std::vector<std::vector<int>> mapGrid = FileReader::MapCharger(mapSrc);

    if (mapGrid.empty())
        return 0;

    Map map(mapGrid);

    Render render;

    std::vector<Entity*> entities;

    std::vector<Entity*> players;

    Player player1(map);

    int maxSteps = 5000;

    SarsaController controller(0.3f,0.96f,2000.0f,-0.1f,0.f,maxSteps);

    controller.LoadQTable(mapSrc);

    player1.SetController(&controller);

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
        std::cout << "\033[H\033[J";  // Esto borra la consola, pero mantén la generación

        std::cout << "Goals: " << goals << " | Generacion: " << generation << " | Pasos: " << controller.steps << " | Epsilon: " << controller.GetEpsilon() << std::endl;
        
        // Imprimimos el contenido de la escena
        std::cout << buffer.str();

        if (map.GetTile(player1.GetX(), player1.GetY()) == TileType::Goal)
        {
            for (int y = 0; y < map.GetHeight(); ++y)
            {
                for (int x = 0; x < map.GetWidth(); ++x)
                {
                    if (map.GetTile(x, y) == TileType::Start)
                    {
                        player1.SetPosition(x, y);
                        controller.steps = 0;
                    }
                }
            }

            generation++;
            goals++;

            if (goals % 4 == 0 && controller.GetEpsilon() > 0.02f)
            {
                controller.SetEpsilon(controller.GetEpsilon() * 0.9f);
            }

        }
        else if (controller.steps > maxSteps)
        {
            for (int y = 0; y < map.GetHeight(); ++y)
            {
                for (int x = 0; x < map.GetWidth(); ++x)
                {
                    if (map.GetTile(x, y) == TileType::Start)
                    {
                        player1.SetPosition(x, y);
                        controller.steps = 0;
                    }
                }
            }

            generation++;
        }

        for (auto entiti : entities)
        {
            entiti->Update(map);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(0));

        if (generation >= 300)
            running = false;
    }

    for (auto e : entities)
    {
        if (e != &player1)
            delete e;
    }

    controller.SaveQTable(mapSrc);

    return 0;
}


void CreateEntity(Map& _map, std::vector<std::vector<int>> _mapGrid, std::vector<Entity*>& entities)
{
    std::vector<EntityStruct> entitiesStructs = FileReader::EntityCharger(_mapGrid);

    for (const auto& es : entitiesStructs)
    {
        switch (es.value)
        {
        case 4:
        {
            Enemy* e = new Enemy(es.col, es.row, _map);
            entities.push_back(e);
            break;
        }

        case 5:
        {
            Treasure* e = new Treasure(es.col, es.row, _map);
            entities.push_back(e);
            break;
        }

        default:
            break;
        }
    }
}