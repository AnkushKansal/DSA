#include <iostream>
#include <vector>
#include <ranges>
#include <stack>

// Time : O(V + E)
// Space : recursive stack O(nodes)
void dfs(int node, const std::vector<std::vector<int>> &graph,
               std::vector<int> &visited, std::stack<int> &ordering)
{
    visited[node] = 1;
    for (auto &neighbor : graph.at(node))
    {
        if (!visited[neighbor])
        {
            dfs(neighbor, graph, visited, ordering);
        }
    }

    ordering.emplace(node); 
    return;
}

// Space : O(nodes)
// Time : O(V for outer loop) + O(V+E for DFS cycle) = O(V+E)
int main()
{
    // Directed graph adjacency list
    const std::vector<std::vector<int>> graph = {
        {},
        {},
        {3},
        {1},
        {0, 1},
        {0, 2},
    };

    auto size = graph.size();
    std::vector<int> visited(size, 0);
    std::stack<int> ordering;

    // for all components
    for (auto index : std::views::iota((size_t)0, size)) // UZ = unsigned long in C++23
    {
        if (!visited[index])
        {
            dfs(index, graph, visited, ordering);
        }
    }

    std::cout << " One Linear ordering of topology is : ";
    while (!ordering.empty())
    {
        const auto &ele = ordering.top();
        std::cout <<  ele << ", ";
        ordering.pop();
    }

    return 0;
}
