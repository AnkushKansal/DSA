#include <iostream>
#include <vector>
#include <ranges>
#include <set>

bool dfs_cycle(int node, const std::vector<std::vector<int>> &graph,
               std::vector<int> &visited,
               std::vector<int> &path,
               std::set<int> &safe_nodes)
{
    visited[node] = true;
    path[node] = true;

    for (auto &neighbor : graph.at(node))
    {
        if (!visited[neighbor])
        {
            if (dfs_cycle(neighbor, graph, visited, path, safe_nodes))
                return true;
        }
        else if (path[neighbor])
        {
            // Found a back edge -> cycle
            return true;
        }
    }

    path[node] = false;
    safe_nodes.insert(node); //O(logn)
    return false;
}


//Time complexity  : O(V+E)logn
//Space : O(nodes) + O(log nodes) for set
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
        {8},
        {9},
    };

    auto size = graph.size();
    std::vector<int> visited(size, 0), track_path(size, 0);
    std::set<int> safe_nodes;

    for (auto index : std::views::iota((size_t)0, size)) // UZ = unsigned long in C++23
    {
        if (!visited[index])
        {
            dfs_cycle(index, graph, visited, track_path, safe_nodes);
        }
    }

    std::cout << "Safe nodes are : ";
    for (auto &ele : safe_nodes)
    {
        std::cout << ele << ", ";
    }

    return 0;
}
