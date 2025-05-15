#ifndef ENEMY_H

#define ENEMY_H

#include "Entity.hpp"

class Enemy : public Entity
{

public:
	Enemy(int startX, int startY, Map& map): Entity(startX, startY, map)
	{
		symbol = '&';
	};

};

#endif
