#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unordered_map>
#include <iostream>
#include <fstream>

class Player;
class Map;
class Entity;

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
    int steps = 0;

    bool reset = false;

    virtual ~Controller() = default;
    virtual void DoAction(Player& player, Map& _map, std::vector<Entity*>& entities) = 0;

    virtual void LoadQTable(const std::string& mapName) = 0;
    virtual void SaveQTable(const std::string& mapName) = 0;
    
    virtual float GetEpsilon() const = 0;
    virtual void SetEpsilon(float _newEpsilon) = 0;

};

#endif
