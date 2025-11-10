#include <array>
#include <queue>
#include <thread>
#include <mutex>
#include <iostream>

constexpr int N = 7;
constexpr int M = 7;

using Grid = std::array<std::array<char, M>, N>;
std::mutex m;

void bfs(const auto &start, const auto &grid, auto &visited, const auto &boundary)
{

    const auto &[max_rows, max_cols] = boundary;
    std::queue<std::pair<int, int>, std::deque<std::pair<int, int>>> nodes_queue;
    nodes_queue.emplace(start);
    visited[start.first][start.second] = 1;

    while (!nodes_queue.empty())
    {

        auto [row, col] = nodes_queue.front();
        nodes_queue.pop();

        constexpr std::array<std::pair<int, int>, 4> dirs = {{{0, -1},  // left
                                                              {0, 1},   // right
                                                              {-1, 0},  // up
                                                              {1, 0}}}; // down

        for (const auto &[dx, dy] : dirs)
        {
            int new_x = row + dx;
            int new_y = col + dy;
            if (new_x >= 0 && new_x < static_cast<int>(max_rows) &&
                new_y >= 0 && new_y < static_cast<int>(max_cols) &&
                grid[new_x][new_y] == '0')
            {
                bool should_enqueue = false;
                {
                    std::scoped_lock lock(m);
                    if (!visited[new_x][new_y])
                    {
                        visited[new_x][new_y] = 1;
                        should_enqueue = true;
                    }
                }

                if (should_enqueue)
                    nodes_queue.emplace(new_x, new_y);
            }
        }
    }
    return;
}

void row_border_bfs(const Grid &grid, Grid &visited, const std::pair<std::size_t, std::size_t> &boundary)
{
    constexpr int row = 0;
    const auto &[rows, cols] = boundary;

    for (std::size_t col = 0; col < cols; ++col)
    {

        // first row
        std::pair start = {row, col};
        if (grid[start.first][start.second] == '0')
            bfs(start, grid, visited, boundary);

        // last row
        start = {rows - 1, col};
        if (grid[start.first][start.second] == '0')
            bfs(start, grid, visited, boundary);
    }
}

void column_border_bfs(const Grid &grid, Grid &visited, const std::pair<std::size_t, std::size_t> &boundary)
{
    constexpr int col = 0;
    const auto &[rows, cols] = boundary;

    for (std::size_t row = 1; row < rows - 1; ++row)
    {
        // first column
        std::pair start = {row, col};
        if (grid[start.first][start.second] == '0')
            bfs(start, grid, visited, boundary);

        // last column
        start = {row, cols - 1};
        if (grid[start.first][start.second] == '0')
            bfs(start, grid, visited, boundary);
    }
}

int main()
{

    constexpr Grid grid = {
        std::array{'X', '0', 'X', 'X', 'X', 'X', 'X'},
        std::array{'X', '0', 'X', '0', 'X', '0', 'X'},
        std::array{'X', '0', 'X', 'X', 'X', '0', 'X'},
        std::array{'X', '0', '0', 'X', 'X', 'X', 'X'},
        std::array{'X', 'X', 'X', '0', '0', '0', 'X'},
        std::array{'X', 'X', 'X', '0', '0', '0', 'X'},
        std::array{'X', 'X', 'X', 'X', 'X', 'X', 'X'},
    };

    Grid visited = {};  // O(n^2)
    Grid output = grid; // O(n^2)

    auto rows = grid.size();
    auto cols = grid.at(0).size();
    auto boundary = std::make_pair(rows, cols);

    std::thread worker1(row_border_bfs, std::cref(grid), std::ref(visited), std::cref(boundary));
    std::thread worker2(column_border_bfs, std::cref(grid), std::ref(visited), std::cref(boundary));

    worker1.join();
    worker2.join();

    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            if (!visited[row][col] && grid[row][col] == '0')
            {
                output[row][col] = 'P';
            }
        }
    }

    std::cout << " Out is :" << "\n";
    for (const auto &row : output)
    {
        for (const auto &col : row)
        {
            std::cout << col << ", ";
        }
        std::cout << "\n";
    }

    return 0;
}