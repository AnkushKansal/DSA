#include <iostream>
#include <queue>
#include <tuple>
#include <array>

constexpr int N = 3;
constexpr int M = 4;

using Grid = std::array<std::array<int, M>, N>;


//Space : O(n*m) for queue and visited  grid
//Time : O(n*m)*4
int main()
{

    constexpr Grid grid = {
        std::array{0, 0, 0, 1},
        std::array{0, 0, 0, 0},
        std::array{0, 0, 1, 0}};

    Grid visited = {0};  // O(n^2)
    Grid distance = {0}; // O(n^2)

    std::queue<std::tuple<int, int, int>> node_queue;

    for (size_t row = 0; row < N; ++row)
    {
        for (size_t col = 0; col < M; ++col)
        {
            if (grid[row][col])
            {
                node_queue.emplace(std::make_tuple(row, col, 0));
                visited[row][col] = 1;
            }
        }
    } // O(n*m)

    while (!node_queue.empty())
    {

        auto [row, col, dist] = node_queue.front();
        node_queue.pop();
        distance[row][col] = dist;

        constexpr std::array<std::pair<int, int>, 4> dirs = {{{0, -1},  // left
                                                              {0, 1},   // right
                                                              {-1, 0},  // up
                                                              {1, 0}}}; // down

        for (const auto &[dx, dy] : dirs)
        {
            int new_x = row + dx;
            int new_y = col + dy;
            if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < M &&
                !visited[new_x][new_y])
            {
                int new_dist = dist + 1;
                node_queue.emplace(std::make_tuple(new_x, new_y, new_dist));
                visited[new_x][new_y] = 1;
            }
        }
    }

    std::cout << "\nDistance grid:\n";
    for (const auto &row : distance)
    {
        for (const auto val : row)
            std::cout << val << ' ';
        std::cout << '\n';
    }
}
