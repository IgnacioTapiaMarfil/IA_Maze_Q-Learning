#ifndef RENDER_H

#define RENDER_H

#include <iostream>
#include <sstream>
#include "Map.hpp"
#include "Entity.hpp"

class Render 
{
public:

    void RenderScene(Map* _map, const std::vector<Entity*>& _entities, std::ostringstream& buffer)
    {
        // Si es la primera vez, creamos el mapa (lo guardamos en el buffer)
        static bool firstRender = true;
        static std::vector<std::vector<char>> sceneBuffer;

        if (firstRender)
        {
            // Inicializamos el buffer de la escena con el mapa
            sceneBuffer.resize(_map->GetHeight(), std::vector<char>(_map->GetWidth(), ' '));

            for (int y = 0; y < _map->GetHeight(); ++y)
            {
                for (int x = 0; x < _map->GetWidth(); ++x)
                {
                    switch (_map->GetGrid()[y][x])
                    {
                    case TileType::Floor:
                        sceneBuffer[y][x] = ' ';
                        break;
                    case TileType::Wall:
                        sceneBuffer[y][x] = '#';
                        break;
                    case TileType::Goal:
                        sceneBuffer[y][x] = 'X';
                        break;
                    case TileType::Start:
                        sceneBuffer[y][x] = ' ';
                        break;
                    default:
                        sceneBuffer[y][x] = ' ';
                        break;
                    }
                }
            }
            firstRender = false;  // El mapa ya se generó una vez
        }

        // Limpiamos el buffer de salida
        buffer.str("");
        buffer.clear();

        for (int y = 0; y < _map->GetHeight(); ++y)
        {
            for (int x = 0; x < _map->GetWidth(); ++x)
            {
                if (sceneBuffer[y][x] != ' ' && sceneBuffer[y][x] != '#' && sceneBuffer[y][x] != 'X' && sceneBuffer[y][x] != 'O' && sceneBuffer[y][x] != '.')
                {
                    if (_map->GetGrid()[y][x] == TileType::Floor)
                        sceneBuffer[y][x] = ' ';
                    else if (_map->GetGrid()[y][x] == TileType::Start)
                        sceneBuffer[y][x] = 'o';
                }
            }
        }

        // Luego, actualizamos las posiciones de las entidades en el buffer
        for (auto e : _entities)
        {
            int entityX = e->GetX();
            int entityY = e->GetY();
            sceneBuffer[entityY][entityX] = e->GetStmbol();
        }

        // Finalmente, imprimimos el buffer completo
        for (int y = 0; y < _map->GetHeight(); ++y)
        {
            for (int x = 0; x < _map->GetWidth(); ++x)
            {
                buffer << sceneBuffer[y][x] << ' ';
            }
            buffer << "\n";
        }
    }
};

#endif
