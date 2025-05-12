#ifndef ENTITY_H

#define ENTITY_H

#include "Map.hpp"

class Entity
{

protected:
	int x, y;

	char symbol = '&';

	bool active = false;

public:
	Entity(int startX, int startY, Map& _map);

	int GetX() const { return x; }
	int GetY() const { return y; }

	char GetStmbol() const{ return symbol; }

	void SetPosition(int newX, int newY);

	bool GetActive() { return active; }
	void SetActive(bool _active) { active = _active; }

	virtual void Update(Map& _map, std::vector<Entity*>& entities) {};

};

#endif // !ENTITY_H
