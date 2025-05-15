#ifndef RENDER_H
#define RENDER_H

#include <iostream>
#include <sstream>
#include "Map.hpp"
#include "Entity.hpp"

class Render 
{
public:

    void RenderScene(Map* _map, const std::vector<Entity*>& _entities, std::ostringstream& buffer);
};

#endif
