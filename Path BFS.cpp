#include "iostream"
#include "queue"
#include "vector"
#include "utility"

// Define directions: up, down, left, right , (Y,X)
const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

std::vector<std::pair<int, int>> bfs(std::vector<std::vector<char>> &grid, std::pair<int, int> start, std::pair<int, int> end)
{
    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<std::pair<int, int>> path;
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<std::pair<int, int>>> parent(rows, std::vector<std::pair<int, int>>(cols, {-1, -1}));

    q.push(start);
    visited[start.first][start.second] = true;

    while (!q.empty())
    {
        std::pair<int, int> current = q.front();
        q.pop();

        if (current == end)
        {
            while (current != start)
            {
                path.push_back(current);
                current = parent[current.first][current.second];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < static_cast<const int>(directions.size()); ++i)
        {
            int new_row = current.first + directions[i].first;
            int new_col = current.second + directions[i].second;

            if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols &&
                grid[new_row][new_col] != '#' && !visited[new_row][new_col])
            {
                q.push({new_row, new_col});
                visited[new_row][new_col] = true;
                parent[new_row][new_col] = current;
            }
        }
    }
    return {};
}

// Function to print grid with path
void printGridWithPath(std::vector<std::vector<char>> &grid, std::vector<std::pair<int, int>> &path)
{
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[0].size(); ++j)
        {
            if (std::make_pair(i, j) == path.front())
                std::cout << 'S' << " ";
            else if (std::make_pair(i, j) == path.back())
                std::cout << 'E' << " ";
            else if (find(path.begin(), path.end(), std::make_pair(i, j)) != path.end())
                std::cout << '*' << " ";
            else
                std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::vector<std::vector<char>> grid = {
        {'.', '.', '.', '#', '.', '.'},
        {'.', '#', '.', '.', '.', '.'},
        {'.', '#', '.', '#', '#', '.'},
        {'.', '.', '#', '.', '.', '.'},
        {'.', '.', '.', '.', '#', '.'},
        {'.', '#', '#', '#', '#', '.'}};

    std::pair<int, int> start = {0, 0};
    std::pair<int, int> end = {5, 5};

    std::vector<std::pair<int, int>> path = bfs(grid, start, end);

    if (!path.empty())
    {
        std::cout << "Shortest path:" << std::endl;
        for (auto &p : path)
        {
            std::cout << "(" << p.first << ", " << p.second << ") ";
        }
        std::cout << std::endl;
        std::cout << "Grid with path:" << std::endl;
        printGridWithPath(grid, path);
    }
    else
    {
        std::cout << "No path found!" << std::endl;
    }

    return 0;
};