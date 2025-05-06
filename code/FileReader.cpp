#include "FileReader.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

EntityStruct::EntityStruct(int _val, int _row, int _col) : value(_val), row(_row), col(_col) {};

std::vector<std::vector<int>> FileReader::MapCharger(const std::string& src)
{
    std::ifstream file(src + ".txt");

    if (!file)
    {
        std::cout << "Error al cargar el archivo";
        return {};
    }

    std::vector<std::vector<int>> map;

    std::string line;
    size_t maxCol = 0;

    while (std::getline(file, line)) 
    {
        std::vector<int> row;

        for (char c : line) 
        {
            if (c >= '0' && c <= '9') 
            {
                /*if (c != '0' && c != '1' && c != '2' && c != '3')
                    c = '0';*/
                row.push_back(c - '0');
            }
        }

        maxCol = std::max(maxCol, row.size());
        map.push_back(row);
    }

    for (auto& fila : map) 
    {
        while (fila.size() < maxCol) 
        {
            fila.push_back(1);
        }
    }

    return map;
}

std::vector<EntityStruct> FileReader::EntityCharger(const std::vector<std::vector<int>>& _map)
{
    if (_map.empty())
    {
        std::cout << "Error al cargar el mapa" << std::endl;
        return {};
    }

    std::vector<EntityStruct> entities;

    int row = 0;

    for (int row = 0; row < _map.size(); ++row)
    {
        for (int col = 0; col < _map[row].size(); ++col)
        {
            if (_map[row][col] >= 4 && _map[row][col] <= 9)
            {
                std::cout << row << ", " << col << ", " << std::endl;

                entities.push_back(EntityStruct(_map[row][col], row, col));
            }
        }
    }

    return entities;
}
