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

    bool MoveUp()
    {
        int newX = owner.GetX();
        int newY = owner.GetY() - 1;

        if (map.IsWalkable(newX, newY))
        {
            owner.SetPosition(newX, newY);

            return true;
        }
        return false;
    }

    bool MoveDown()
    {
        int newX = owner.GetX();
        int newY = owner.GetY() + 1;

        if (map.IsWalkable(newX, newY))
        {
            owner.SetPosition(newX, newY);

            return true;
        }
        return false;
    }

    bool MoveLeft()
    {
        int newX = owner.GetX() - 1;
        int newY = owner.GetY();

        if (map.IsWalkable(newX, newY))
        {
            owner.SetPosition(newX, newY);

            return true;
        }
        return false;
    }

    bool MoveRight()
    {
        int newX = owner.GetX() + 1;
        int newY = owner.GetY();

        if (map.IsWalkable(newX, newY))
        {
            owner.SetPosition(newX, newY);

            return true;
        }
        return false;
    }

    bool Move(int dx, int dy) 
    {
        int newX = owner.GetX() + dx;
        int newY = owner.GetY() + dy;

        if (map.IsWalkable(newX, newY))
        {
            owner.SetPosition(newX, newY);

            return true;
        }

        return false;
    }
};


#endif // !MOVEMVENTCOMPONENT_H