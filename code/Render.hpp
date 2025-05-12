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
        static bool firstRender = true;
        static std::vector<std::vector<char>> sceneBuffer;

        if (firstRender)
        {
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
            firstRender = false;
        }

        // Limpieza de entidades antiguas en el buffer (dejamos mapa intacto)
        for (int y = 0; y < _map->GetHeight(); ++y)
        {
            for (int x = 0; x < _map->GetWidth(); ++x)
            {
                // Si no es parte fija del mapa, limpiamos el carácter
                if (sceneBuffer[y][x] != '#' && sceneBuffer[y][x] != 'X')
                    sceneBuffer[y][x] = ' ';
            }
        }

        // Dibujar entidades activas
        for (auto e : _entities)
        {
            if (!e->GetActive()) continue;

            int entityX = e->GetX();
            int entityY = e->GetY();
            sceneBuffer[entityY][entityX] = e->GetStmbol();
        }

        // Volcar el buffer al string
        buffer.str("");
        buffer.clear();

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
