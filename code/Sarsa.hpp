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
    Action nextAction = Action::Up;


    std::unordered_map<std::pair<State, Action>, float, StateActionHash> qTable;

    std::mt19937 rng;
    std::uniform_real_distribution<float> dist;

public:
    bool firstIteration;

    SarsaController(float _learningRate, float _discountRate, float _goalReward, float _movementReward, float _colisionReward, float _epsilon, float _killReward, float _treasureReward, float _dieReward, float _goingBackReward, int _maxSteps)
        : learningRate(_learningRate), discountRate(_discountRate), goalReward(_goalReward), movementReward(_movementReward), colisionReward(_colisionReward), epsilon(_epsilon), killReward(_killReward), treasureReward(_treasureReward), dieReward(_dieReward), goingBackReward(_goingBackReward), maxSteps(_maxSteps)
    {
        std::random_device rd;
        rng.seed(rd());

        steps = 0;

        firstIteration = true;
    }


    void DoAction(Player& player, Map& _map, std::vector<Entity*>& _entities) override;

    void SaveQTable(const std::string& mapName);

    void LoadQTable(const std::string& mapName);

    void SetEpsilon(float _newEpsilon) override { epsilon = _newEpsilon; }
    float GetEpsilon() const { return epsilon; }


private:

    Action ChooseAction(State _state);

    float GetQValue(const State& _state, Action _action);

    void SetQValue(const State& _state, Action _action, float value);
};

#endif
