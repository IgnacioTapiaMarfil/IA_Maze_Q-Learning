#ifndef SARSA_H
#define SARSA_H

#include "Controller.hpp"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <random>

#include "Player.hpp"

class SarsaController : public Controller
{
private:

    float learningRate;
    float discountRate;
    float epsilon;
    float goalReward;
    float movementReward;
    float colisionReward;
    float killReward;
    float treasureReward;
    float dieReward;
    float goingBackReward;

    int maxSteps;

    State previousState;
    Action nextAction;


    std::unordered_map<std::pair<State, Action>, float, StateActionHash> qTable;

    std::mt19937 rng;
    std::uniform_real_distribution<float> dist; //se usan para los numeros aleatorios en el e-greedy

public:
    bool firstIteration;

    SarsaController(float _learningRate, float _discountRate, float _goalReward, float _movementReward, float _colisionReward, float _epsilon, float _killReward, float _treasureReward, float _dieReward, float _goingBackReward, int _maxSteps)
        : learningRate(_learningRate), discountRate(_discountRate), goalReward(_goalReward), movementReward(_movementReward), colisionReward(_colisionReward), epsilon(_epsilon), killReward(_killReward), treasureReward(_treasureReward), dieReward(_dieReward), goingBackReward(_goingBackReward), maxSteps(_maxSteps)
    {
        std::random_device rd;  //se usan para los numeros aleatorios en el e-greedy
        rng.seed(rd());

        steps = 0;

        firstIteration = true;
    }


    void DoAction(Player& player, Map& _map, std::vector<Entity*>& _entities) override;

    //* funciones para cargar y guardar la table*//
    void SaveQTable(const std::string& mapName)
    {
        std::ofstream file(mapName + "_qtable.txt");

        if (!file.is_open()) 
        {
            std::cout << "Error al guardar la Q-table\n";
            return;
        }

        for (const auto& pair : qTable)
        {
            State s = pair.first.first;
            int action = static_cast<int>(pair.first.second);
            float value = pair.second;

            file << s.first << " " << s.second << " " << action << " " << value << "\n";
        }

        std::cout << "archivo creado";
        file.close();
    }

    void LoadQTable(const std::string& mapName)
    {
        std::ifstream file(mapName + "_qtable.txt");

        if (!file.is_open()) {
            std::cerr << "Error al cargar la Q-table\n";
            return;
        }

        int x, y, actionInt;
        float q;
        while (file >> x >> y >> actionInt >> q)
        {
            State s = { x, y };
            Action a = static_cast<Action>(actionInt);
            qTable[{s, a}] = q;
        }

        file.close();
    }

    void SetEpsilon(float _newEpsilon) override { epsilon = _newEpsilon; }
    float GetEpsilon() const { return epsilon; }


private:

    Action ChooseAction(State _state);

    float GetQValue(const State& _state, Action _action);

    void SetQValue(const State& _state, Action _action, float value);
};

#endif
