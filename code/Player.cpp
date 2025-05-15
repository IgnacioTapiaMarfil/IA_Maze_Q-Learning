#include "Player.hpp"
#include "Enemy.hpp"
#include "Treasure.hpp"

#include <random>
#include <iostream>

Player::Player(Map& _map) : Entity(0,0, _map), movementComponent(*this, _map)
{
    symbol = '@';

    dead = false;

    kill = false;

    arrive = false;

    treasureCatched = false;

    treasuresCaught         = 0;
    totalTreasuresCaught    = 0;
    enemiesKilled           = 0;
    totalEnemiesKilled      = 0;
    deaths                  = 0;

    for (int y = 0; y < _map.GetHeight(); ++y) 
    {
        for (int x = 0; x < _map.GetWidth(); ++x) 
        {
            if (_map.GetTile(x, y) == TileType::Start) 
            {
                StartPosX = x;
                StartPosX = y;
                SetPosition(StartPosX, StartPosX);
                return;
            }
        }
    }

    std::cerr << "Start tile not found! PlayerStartSet to (0,0)\n";
}

void Player::Update(Map& _map, std::vector<Entity*>& _entities)
{
    for (size_t i = 0; i < _entities.size(); i++)
    {
        if (!_entities[i]->GetActive())
            continue;

        if (_entities[i]->GetX() == x && _entities[i]->GetY() == y)
        {
            if (Enemy* enemy = dynamic_cast<Enemy*>(_entities[i]))
            {
                Fight(enemy);
            }
            else if (Treasure* treasure = dynamic_cast<Treasure*>(_entities[i]))
            {
                treasureCatched = true;
                treasuresCaught++;
                totalTreasuresCaught++;

                _entities[i]->SetActive(false);
            }
        }
    }

    if (controller) controller->DoAction(*this, _map, _entities);
}

void Player::Reset()
{
    SetPosition(StartPosX, StartPosX);

    dead = false;

    kill = false;

    arrive = false;

    treasureCatched = false;

    treasuresCaught = 0;
    enemiesKilled = 0;
}

void Player::Fight(Entity* _enemy)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    float random = dis(gen);

    if (random <= 0.5f)
    {
        _enemy->SetActive(false);
        kill = true;
        enemiesKilled++;
        totalEnemiesKilled++;
    }
    else
    {
        dead = true;
        deaths++;
    }
}
