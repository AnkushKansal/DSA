#include <iostream>
#include <vector>
#include <unordered_map>

bool dfs_cycle(int node, const std::unordered_map<int, std::vector<int>> &graph,
               std::unordered_map<int, bool> &visited,
               std::unordered_map<int, bool> &path)
{
    visited[node] = true;
    path[node] = true;

    auto it = graph.find(node);
    if (it != graph.end())
    {
        for (auto &neighbor : it->second)
        {
            if (!visited[neighbor])
            {
                if (dfs_cycle(neighbor, graph, visited, path))
                    return true;
            }
            else if (path[neighbor])
            {
                // Found a back edge -> cycle
                return true;
            }
        }
    }

    path[node] = false;
    return false;
}

bool has_cycle(const std::unordered_map<int, std::vector<int>> &graph)
{
    std::unordered_map<int, bool> visited, path;

    for (auto &[node, _] : graph)
    {
        if (!visited[node])
        {
            if (dfs_cycle(node, graph, visited, path))
                return true;
        }
    }
    return false;
}

int main()
{
    // Directed graph
    const std::unordered_map<int, std::vector<int>> graph = {
        {1, {2}},
        {2, {3}},
        {3, {4}},
        {4, {2}} // cycle here (2 -> 3 -> 4 -> 2)
    };

    if (has_cycle(graph))
        std::cout << "Cycle detected!\n";
    else
        std::cout << "No cycle detected.\n";
}
