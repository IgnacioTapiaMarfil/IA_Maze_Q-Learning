#ifndef TREASURE_H

#define TREASURE_H

#include "Entity.hpp"

class Treasure : public Entity
{

public:
	Treasure(int startX, int startY, Map& map) : Entity(startX, startY, map)
	{
		symbol = '$';
	};

};

#endif
