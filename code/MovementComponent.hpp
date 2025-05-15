#ifndef MOVEMVENTCOMPONENT_H

#define MOVEMVENTCOMPONENT_H

#include <iostream>

class Entity;
class Map;

class MovementComponent {
private:
    Entity& owner;
    Map& map;

public:
    MovementComponent(Entity& entity, Map& gameMap) : owner(entity), map(gameMap) {}

    bool MoveUp();

    bool MoveDown();

    bool MoveLeft();

    bool MoveRight();

    bool Move(int dx, int dy);
};


#endif // !MOVEMVENTCOMPONENT_H