#include "Q-Learning.hpp"
#include <iostream>


void QLearningController::DoAction(Player& _player, Map& _map)
{
    int x = _player.GetX();
    int y = _player.GetY();

    State state = { x, y };

    Action action = ChooseAction(state);

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

    if (steps >= maxSteps)
    {
        reward -= 100;
        _player.SetDead(true);
    }

    if (nextState == previousState)
    {
        reward += -0.4f;
    }

    if (_map.GetTile(newX, newY) == TileType::Goal)
    {
        reward += goalReward;
        _player.SetArrive(true);
    }

    float currentQ = GetQValue(state, action);

    float nextQ = -1e9;

    for (int i = 0; i < 4; ++i)
    {
        Action a = static_cast<Action>(i);
        float q = GetQValue(nextState, a);
        if (q > nextQ)
            nextQ = q;
    }

    float tdError = reward + discountRate * nextQ - currentQ;
    float updatedQ = currentQ + learningRate * tdError;

    steps++;

    SetQValue(state, action, updatedQ);

    previousState = state;

}

Action QLearningController::ChooseAction(State _state)
{

    if (dist(rng) < epsiolon)
    {
        int random = rand() % 4;
        std::cout << "random \n";
        return static_cast<Action>(random);
    }

    std::cout << "Select \n";
    float bestValue = -1e9; //numero muy pequeño se puede cambiar por -inf pero me da un problema con que inf sea const

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

float QLearningController::GetQValue(const State& _state, Action _action)
{
    auto key = std::make_pair(_state, _action);

    if (qTable.find(key) == qTable.end())
        qTable[key] = 0.0f;


    return qTable[key];
}

void QLearningController::SetQValue(const State& _state, Action _action, float value)
{
    auto key = std::make_pair(_state, _action);
    qTable[key] = value;
}
