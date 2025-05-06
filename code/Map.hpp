#ifndef MAP_H

#define MAP_H

#include <iostream>
#include <vector>

enum class TileType
{
	Floor = 0,
	Wall  = 1,
	Goal  = 2,
	Start = 3
};
class Map
{

protected:
	std::vector<std::vector<TileType>> grid;

	int width, height;

public:
	Map(std::vector<std::vector<int>>);

	TileType GetTile(int x, int y) const;

	std::vector<std::vector<TileType>> GetGrid() { return grid; }
	int GetWidth()  const { return width;  }
	int GetHeight() const { return height; }

	bool IsWalkable(int x, int y) const;
};


#endif // !MAP_H