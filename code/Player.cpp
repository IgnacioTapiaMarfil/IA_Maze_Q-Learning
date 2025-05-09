#include "Player.hpp"

Player::Player(Map& _map) : Entity(0,0, _map), movementComponent(*this, _map)
{
    symbol = '@';

    for (int y = 0; y < _map.GetHeight(); ++y) 
    {
        for (int x = 0; x < _map.GetWidth(); ++x) 
        {
            if (_map.GetTile(x, y) == TileType::Start) 
            {
                SetPosition(x, y);
                return;
            }
        }
    }

    std::cerr << "Start tile not found! PlayerStartSet to (0,0)\n";
}

void Player::Update(Map& _map, std::vector<Entity*>& entities)
{
    if (controller) controller->DoAction(*this, _map);

}