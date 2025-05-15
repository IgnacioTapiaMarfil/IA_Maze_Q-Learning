
#include "MovementComponent.hpp"

#include "Entity.hpp"

bool MovementComponent::MoveUp()
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

bool MovementComponent::MoveDown()
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

bool MovementComponent::MoveLeft()
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

bool MovementComponent::MoveRight()
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

bool MovementComponent::Move(int dx, int dy)
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