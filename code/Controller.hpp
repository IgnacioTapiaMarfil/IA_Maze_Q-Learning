#ifndef CONTROLLER_H
#define CONTROLLER_H

class Player;
class Map;

class Controller 
{
public:
    virtual ~Controller() = default;
    virtual void DoAction(Player& player, Map& _map) = 0;
};

#endif
