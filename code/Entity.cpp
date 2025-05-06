#include "Entity.hpp"

#include <queue>
#include <utility>

Entity::Entity(int startX, int startY, Map& _map) : x(startX), y(startY)
{
    //* Para que si se genera la entidad en una pared busque el suelo mas cercano*//

    if (_map.IsWalkable(startX, startY))
    {
        x = startX;
        y = startY;
        return;
    }

    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited(_map.GetHeight(), std::vector<bool>(_map.GetWidth(), false));

    q.push({ startX, startY });
    visited[startY][startX] = true;

    const int dx[] = { 1, -1, 0, 0 };
    const int dy[] = { 0, 0, 1, -1 };

    while (!q.empty())
    {
        std::pair<int, int> current = q.front();
        int cx = current.first;
        int cy = current.second;

        q.pop();

        if (_map.IsWalkable(cx, cy))
        {
            x = cx;
            y = cy;
            return;
        }

        for (int i = 0; i < 4; ++i)
        {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx >= 0 && ny >= 0 && nx < _map.GetWidth() && ny < _map.GetHeight() && !visited[ny][nx])
            {
                visited[ny][nx] = true;
                q.push({ nx, ny });
            }
        }
    }

    std::cerr << "Error: No se encontró suelo cerca de la posición (" << startX << ", " << startY << ")" << std::endl;
    x = y = -1;
}

void Entity::SetPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}
