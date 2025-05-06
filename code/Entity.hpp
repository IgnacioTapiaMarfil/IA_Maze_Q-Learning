#ifndef ENTITY_H

#define ENTITY_H

#include "Map.hpp"

class Entity
{

protected:
	int x, y;

	char symbol = '&';

public:
	Entity(int startX, int startY, Map& _map);

	int GetX() const { return x; }
	int GetY() const { return y; }

	char GetStmbol() const{ return symbol; }

	void SetPosition(int newX, int newY);

	virtual void Update(Map& _map) {};

};

#endif // !ENTITY_H
