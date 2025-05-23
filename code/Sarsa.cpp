#include "Sarsa.hpp"
#include <iostream>


void SarsaController::DoAction(Player& _player, Map& _map, std::vector<Entity*>& _entities)
{
    int x = _player.GetX();
    int y = _player.GetY();

    State state = { x, y };

    Action action;

    if (firstIteration)
    {
        action = ChooseAction(state);
        firstIteration = false;
    }
    else
    {
        action = nextAction;
    }

    bool moved = false;
    MovementComponent movement = _player.GetMovementComponent();

    int newX = x, newY = y;

    switch (action) 
    {
        case Action::Up:    moved = movement.MoveUp();    if (moved) newY--; break;

        case Action::Down:  moved = movement.MoveDown();  if (moved) newY++; break;

        case Action::Left:  moved = movement.MoveLeft();  if (moved) newX--; break;

        case Action::Right: moved = movement.MoveRight(); if (moved) newX++; break;
    }

    State nextState = { newX, newY };

    float reward;

    if (moved)
        reward = movementReward;
    else
        reward = colisionReward;
    
    if (_player.GetDead())
    {
        reward += dieReward;
        std::cout << "Muerto\n";
        reset = true;
    }

    if (_player.GetKill())
    {
        reward += killReward;
        std::cout << "kill\n";
        _player.SetKill(false);
    }

    if (_player.GetTreasureCached())
    {
        reward += treasureReward;
        std::cout << "tesoro\n";
        _player.SetTreasureCached(false);
    }

    if (steps >= maxSteps)
    {
        reward += dieReward;
        reset = true;
    }

    if (nextState == previousState)
    {
        reward += goingBackReward;
    }

    if (_map.GetTile(newX, newY) == TileType::Goal)
    {
        reward += goalReward;
        _player.SetArrive(true);
        reset = true;
    }

    nextAction = ChooseAction(nextState);

    float currentQ = GetQValue(state, action);
    float nextQ = GetQValue(nextState, nextAction);

    float tdError = reward + discountRate * nextQ - currentQ;
    float updatedQ = currentQ + learningRate * tdError;

    std::cout << "valor = " << updatedQ << "\n";
    steps++;

    SetQValue(state, action, updatedQ);

    previousState = state;
}

Action SarsaController::ChooseAction(State _state)
{

    if (dist(rng) < epsilon)
    {
        int random = rand() % 4;
        return static_cast<Action>(random);
    }

    float bestValue = -1e9;

    Action bestAction = Action::Up;

    for (int i = 0; i < 4; ++i)
    {
        Action a = static_cast<Action>(i);

        float q = GetQValue(_state, a);

        if (q > bestValue)
        {
            bestValue = q;
            bestAction = a;
        }
    }

    return bestAction;
}

float SarsaController::GetQValue(const State& _state, Action _action)
{
    auto key = std::make_pair(_state, _action);

    if (qTable.find(key) == qTable.end())
        qTable[key] = 0.0f;


    return qTable[key];
}

void SarsaController::SetQValue(const State& _state, Action _action, float value)
{
    auto key = std::make_pair(_state, _action);
    qTable[key] = value;
}


//* funciones para cargar y guardar la table*//
void SarsaController::SaveQTable(const std::string& mapName)
{
    std::ofstream file(mapName + "_qtable_Sarsa.txt");

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

void SarsaController::LoadQTable(const std::string& mapName)
{
    std::ifstream file(mapName + "_qtable_Sarsa.txt");

    if (!file.is_open()) 
    {
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