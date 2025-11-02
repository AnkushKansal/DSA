#include <unordered_map>
#include <ranges>
#include <algorithm>
#include <cassert>
#include <stack>
#include "graph_repr_weighted_list.h"

void depth_first_traversal(auto &root, auto &graph, auto &visited)
{
    std::stack<u_short, std::deque<u_short>> nodes_stack;
    nodes_stack.emplace(root);

    while (!nodes_stack.empty())
    {
        u_short ele = nodes_stack.top();
        nodes_stack.pop();

        if (!visited[ele])
        {
            for (auto &edges : graph[ele])
            {
                // loops twice for single edge
                if (!visited[edges.first])
                    nodes_stack.emplace(edges.first);
            }
            std::cout << "Visited Node Index -> " << ele << "\n";
            visited[ele] = 1;
        }
    }
}

// Undirected Graph/Tree
// Space : O(nodes)
// Time : O(nodes + 2edges)
// O(nodes)for visited map + O(nodes) for outer loop + (O(nodes)+ O(2Edges) for DFS
int main()
{
    auto graph = get_graph_list();

    std::unordered_map<u_short, short> visited;
    for (auto &edges_vec : graph)
    {
        for (auto &edge : edges_vec.second)
        {
            if (visited.find(edge.first) == visited.end())
                visited[edge.first] = 0;
        }
    }

    short compo_count = 0;

    for (auto &entry : visited)
    {
        if (!visited[entry.first])
        {
            depth_first_traversal(entry.first, graph, visited);
            ++compo_count;
        }
    }

    std::cout << "Total components in given graph : " << compo_count << "\n";
    return 0;
}