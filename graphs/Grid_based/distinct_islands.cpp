#include <array>
#include <stack>
#include <set>
#include <vector>
#include <iostream>

constexpr int N = 6;
constexpr int M = 8;

using Grid = std::array<std::array<int, M>, N>;

// Space : O(n*m)
// Time : O(n*m*4)
std::vector<std::pair<size_t, size_t>> dfs(const auto &start, const auto &grid, auto &visited, const auto &boundary)
{

    auto &[max_rows, max_cols] = boundary;
    std::stack<std::pair<size_t, size_t>, std::deque<std::pair<size_t, size_t>>> nodes_stack;
    nodes_stack.emplace(start);
    visited[start.first][start.second] = 1;

    std::vector<std::pair<size_t, size_t>> adjacent;

    constexpr std::array<std::pair<int, int>, 4> dirs = {{{0, -1},  // left
                                                          {0, 1},   // right
                                                          {-1, 0},  // up
                                                          {1, 0}}}; // down

    while (!nodes_stack.empty())
    {
        auto [row, col] = nodes_stack.top();
        nodes_stack.pop();
        adjacent.emplace_back(std::make_pair(row - start.first, col - start.second)); // transform the cell to base, O(log n*m)
        std::cout << "Visited : [" << row << "," << col << "]" << "\n";

        for (const auto &[dx, dy] : dirs)
        {
            auto new_x = row + dx;
            auto new_y = col + dy;
            if (new_x >= 0 && new_x < max_rows && new_y >= 0 && new_y < max_cols &&
                grid[new_x][new_y] && !visited[new_x][new_y])
            {
                nodes_stack.emplace(new_x, new_y);
                visited[new_x][new_y] = 1;
            }
        }
    }

    return adjacent;
}

// Space : O(n*m)
// Time : O(n*m + n*m*(4+logn) for dfs)
int main()
{

    constexpr Grid grid = {
        std::array{1, 1, 0, 1, 0, 1, 0, 0},
        std::array{1, 1, 0, 1, 0, 0, 1, 0},
        std::array{0, 1, 0, 1, 0, 0, 0, 0},
        std::array{0, 0, 0, 0, 0, 0, 1, 1},
        std::array{1, 0, 0, 0, 0, 0, 1, 1},
        std::array{1, 0, 0, 0, 0, 0, 0, 1},
    };

    const auto rows = grid.size();
    const auto cols = grid.at(0).size();
    std::pair<size_t, size_t> boundary = {rows, cols};

    std::vector<std::vector<int>> visited(rows, std::vector<int>(cols, 0)); // O(n^2)

    std::set<std::vector<std::pair<size_t, size_t>>> islands;

    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            if (!visited[row][col] && grid[row][col])
            {
                auto start = std::make_pair(row, col);
                islands.insert(dfs(start, grid, visited, boundary));
            }
        }
    }

    std::cout << "Distinct islands are : " << islands.size() << "\n";
    return 0;
}