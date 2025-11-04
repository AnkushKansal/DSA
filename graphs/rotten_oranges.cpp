#include <array>
#include <stack>
#include <iostream>

constexpr int N = 4;
constexpr int M = 4;

using Grid = std::array<std::array<int, M>, N>;

// Time : O(n^2)*4
// Space : O(matrix size) or O(n^2) for stack
auto rotting_oranges(const auto &start, Grid &grid, Grid &visited)
{

    static int rotting_time = 0;
    std::stack<std::pair<int, int>> cell_stack;
    cell_stack.emplace(start);

    while (!cell_stack.empty())
    {
        auto [row, col] = cell_stack.top();
        cell_stack.pop();

        constexpr std::array<std::pair<int, int>, 4> dirs = {{{0, -1},  // left
                                                              {0, 1},   // right
                                                              {-1, 0},  // up
                                                              {1, 0}}}; // down

        bool rot_flag = false;
        for (auto &dir : dirs)
        {
            int new_x = row + dir.first;
            int new_y = col + dir.second;
            if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < M &&
                grid[new_x][new_y] != 0 && !visited[new_x][new_y])
            {
                cell_stack.emplace(std::make_pair(new_x, new_y));
                grid[new_x][new_y] = 2;
                if (!rot_flag)
                    rot_flag = true;
            }
        }
        std::cout << "Visited : [" << row << "," << col << "]" << "\n";
        visited[row][col] = 1;
        if (rot_flag)
        {
            ++rotting_time;
        }
    }
    return rotting_time;
}

// Space : (n^2) for auxiliary matrix
// Time = O(n^2)
int main()
{

    Grid grid = {
        std::array{0, 1, 2, 1},
        std::array{0, 0, 0, 0},
        std::array{0, 2, 1, 0},
        std::array{0, 2, 1, 1}};

    Grid visited = {};

    int total_rotting_time = 0;

    for (auto row = 0U; row < N; ++row)
    {
        for (auto col = 0U; col < M; ++col)
        {
            if (grid[row][col] == 2 && visited[row][col] != 1)
            {
                auto start = std::make_pair(row, col);
                total_rotting_time = rotting_oranges(start, grid, visited);
            }
        }
    }

    std::cout << "\nUpdated grid:\n";
    for (const auto &row : grid)
    {
        for (const auto val : row)
            std::cout << val << ' ';
        std::cout << '\n';
    }

    std::cout << "total_rotting_time : " << total_rotting_time << "\n";
    return 0;
}