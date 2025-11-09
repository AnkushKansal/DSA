#include <array>
#include <stack>
#include <cassert>
#include <iostream>

constexpr int N = 6;
constexpr int M = 6;

using Grid = std::array<std::array<int, M>, N>;

// Time : O(n^2)*4
// Space : O(matrix size) or O(n^2) for stack
void fill_image_grid(const auto &start, Grid &grid, const auto &new_pixel)
{
    const int old_pixel = grid[start.first][start.second];
    if (old_pixel == new_pixel)
        return;

    std::stack<std::pair<int, int>> cell_stack;
    cell_stack.emplace(start);
    grid[start.first][start.second] = new_pixel;

    constexpr std::array<std::pair<int, int>, 4> dirs = {{{0, -1},  // left
                                                          {0, 1},   // right
                                                          {-1, 0},  // up
                                                          {1, 0}}}; // down

    while (!cell_stack.empty())
    {
        auto [row, col] = cell_stack.top();
        cell_stack.pop();
        std::cout << "Visited : [" << row << "," << col << "]" << "\n";

        for (const auto &[dx, dy] : dirs)
        {
            int new_x = row + dx;
            int new_y = col + dy;
            if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < M &&
                grid[new_x][new_y] == old_pixel)
            {
                cell_stack.emplace(new_x, new_y);
                grid[new_x][new_y] = new_pixel;
            }
        }
    }
}

// Space : O(1)
// Time = O(n^2) for stack
int main()
{

    Grid grid = {
        std::array{2, 3, 5, 6, 0, 2},
        std::array{2, 2, 1, 1, 3, 0},
        std::array{0, 2, 2, 2, 0, 0},
        std::array{0, 2, 2, 1, 0, 0},
        std::array{0, 0, 0, 1, 0, 0},
        std::array{0, 2, 2, 0, 0, 1}};

    int new_pixel = 0;
    std::cout << "Enter new pixel : ";
    std::cin >> new_pixel;

    int start_row = 0, start_col = 0;
    std::cout << "Enter start grid less than " << N << " and " << M << " : ";
    std::cin >> start_row >> start_col;
    assert(start_row < N && start_row >= 0);
    assert(start_col < M && start_col >= 0);

    auto start = std::make_pair(start_row, start_col);
    fill_image_grid(start, grid, new_pixel);

    std::cout << "\nUpdated grid:\n";
    for (const auto &row : grid)
    {
        for (const auto val : row)
            std::cout << val << ' ';
        std::cout << '\n';
    }

    return 0;
}