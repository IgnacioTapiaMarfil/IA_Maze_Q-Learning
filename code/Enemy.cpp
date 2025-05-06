#include "Enemy.hpp"

Enemy::Enemy(int startX, int startY, Map& map) : Entity(startX, startY, map)
{
    symbol = '&';
}
