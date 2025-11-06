#include <array>
#include <queue>
#include <iostream>

constexpr int N = 6;
constexpr int M = 6;

using Grid = std::array<std::array<int, M>, N>;

// Time : O(n^2)*8
// Space : O(matrix size)/  O(n^2) for queue
void traverse(const auto &start, const Grid &grid, Grid &visited)
{

    std::queue<std::pair<int, int>> cell_queue;
    cell_queue.emplace(start);
    visited[start.first][start.second] = 1;

    while (!cell_queue.empty())
    {
        auto &[row, col] = cell_queue.front();
        cell_queue.pop();
        std::cout << "Visited : [" << row << "," << col << "]" << "\n";

        constexpr std::array<std::pair<int, int>, 8> dirs = {{{0, -1},  // left
                                                              {0, 1},   // right
                                                              {-1, 0},  // up
                                                              {1, 0},   // down
                                                              {-1, -1}, // left up
                                                              {-1, 1},  // right up
                                                              {1, -1},  // left down
                                                              {1, 1}}}; // right down
        for (const auto &[dx, dy] : dirs)
        {
            int new_x = row + dx;
            int new_y = col + dy;
            if (new_x >= 0 && new_x < N &&
                new_y >= 0 && new_y < M &&
                grid[new_x][new_y] == 1 && !visited[new_x][new_y])
            {
                cell_queue.emplace(std::make_pair(new_x, new_y));
                visited[new_x][new_y] = 1;
            }
        }
    }
}

// Time : O(n^2) for outer loop
// Space : (n^2) for auxiliary matrix
//  Total Time = O(n^2)
int main()
{

    Grid grid = {
        std::array{0, 1, 1, 1, 0, 0},
        std::array{0, 0, 1, 1, 0, 0},
        std::array{0, 0, 0, 0, 0, 0},
        std::array{0, 1, 1, 1, 0, 0},
        std::array{0, 0, 0, 1, 0, 0},
        std::array{0, 1, 1, 0, 0, 1}};

    Grid visited = {};
    int islands = 0;

    for (size_t row = 0; row < N; ++row)
    {
        for (size_t col = 0; col < M; ++col)
        {
            if (grid[row][col] == 1 && visited[row][col] != 1)
            {
                auto start = std::make_pair(row, col);
                traverse(start, grid, visited);
                ++islands;
            }
        }
    }

    std::cout << "Total islands are  :" << islands << "\n";
}