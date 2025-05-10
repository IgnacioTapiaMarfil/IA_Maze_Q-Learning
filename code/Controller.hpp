#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unordered_map>
#include <iostream>
#include <fstream>

class Player;
class Map;

using State = std::pair<int, int>;
enum class Action { Up = 0, Down = 1, Left = 2, Right = 3 };

struct StateActionHash
{
    std::size_t operator()(const std::pair<State, Action>& k) const
    {
        return std::hash<int>()(k.first.first)
            ^ std::hash<int>()(k.first.second << 2)
            ^ std::hash<int>()(static_cast<int>(k.second) << 4);
        // desplazo 2 y 4 bits la Y y la accion para distingir mas unos EstadoAccion de otros
    }
};

class Controller 
{
public:
    virtual ~Controller() = default;
    virtual void DoAction(Player& player, Map& _map) = 0;
};

#endif
