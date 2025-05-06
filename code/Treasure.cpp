#include "Treasure.hpp"

Treasure::Treasure(int startX, int startY, Map& map) : Entity(startX, startY, map)
{
    symbol = '$';
}
