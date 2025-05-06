#include "Map.hpp"

Map::Map(std::vector<std::vector<int>> _grid)
{
    height = static_cast<int>(_grid.size());
    width = height > 0 ? static_cast<int>(_grid[0].size()) : 0;

    grid.resize(height, std::vector<TileType>(width, TileType::Floor));

    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            switch (_grid[y][x]) 
            {
                case 0:  grid[y][x] = TileType::Floor; break;
                case 1:  grid[y][x] = TileType::Wall;  break;
                case 2:  grid[y][x] = TileType::Goal;  break;
                case 3:  grid[y][x] = TileType::Start; break;
                default: grid[y][x] = TileType::Floor; break;
            }
        }
    }
}

TileType Map::GetTile(int x, int y) const
{
    if (x < 0 || y < 0 || x >= width || y >= height) return TileType::Floor;
    return grid[y][x];
}

bool Map::IsWalkable(int x, int y) const
{
    return GetTile(x, y) != TileType::Wall;
}
