#include <iostream>
#include <vector>
#include <ranges>

bool dfs_cycle(int node, const std::vector<std::vector<int>> &graph,
               std::vector<int> &visited)
{
    visited[node] = 1; // visiting
    for (auto &neighbor : graph.at(node))
    {
        if (!visited[neighbor])
        {
            if (dfs_cycle(neighbor, graph, visited))
                return true;
        }
        else if (visited[neighbor] == 1)
        {
            // Found a back edge -> cycle
            return true;
        }
    }

    visited[node] = 2; // visited
    return false;
}


//Space : O(nodes)
//Time : O(V for outer loop) + O(V+E for DFS cycle) = O(V+E)
int main()
{
    // Directed graph
    const std::vector<std::vector<int>> graph = {
        {1},
        {2},
        {3},
        {4, 5},
        {6},
        {6},
        {7},
        {},
        {1, 9},
        {10},
        {2},
        {9},
    };

    auto size = graph.size();
    std::vector<int> visited(size, 0);

    bool cycle = false;
    for (auto index : std::views::iota((size_t)0, size)) // UZ = unsigned long in C++23
    {
        if (!visited[index])
        {
            cycle = dfs_cycle(index, graph, visited);
            if(cycle)
                break;
        }
    }

    cycle ? std::cout << "Cycle detected " : std::cout << "No Cycle detected ";

    return 0;
}
