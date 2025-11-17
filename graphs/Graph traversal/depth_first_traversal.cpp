// depth Wise traversal

#include <cassert>
#include <stack>
#include <ranges>
#include <algorithm>
#include <unordered_map>

#include "../Graph_representation/graph_repr_weighted_list.h"

// Undirected Graph/Tree
// Space : O(nodes) for stack
// Time : O(nodes + 2*edges)  //(O(nodes) for visited map + (O(nodes)+ O(2Edges))
int main()
{
    const auto& graph = get_graph_list();

    // Assumption : Graph is sparse. Use vector if dense
    std::unordered_map<u_short, short> visited;
    for (const auto &[node, edges] : graph)
    {
        for (const auto &[edge, weight] : edges)
        {
            visited[edge] = 0;
        }
    }

    u_short root = 1;
    std::cout << "Enter Root Node : ";
    std::cin >> root;
    auto [min, max] = std::ranges::minmax_element(visited, std::less<>(), &decltype(visited)::value_type::first); // compare by key
    assert(min != visited.end() && max != visited.end());
    assert(root <= max->first && root >= min->first);

    std::stack<u_short, std::deque<u_short>> nodes_stack;
    nodes_stack.emplace(root);
    visited[root] = 1;

    while (!nodes_stack.empty())
    {
        u_short node = nodes_stack.top();
        nodes_stack.pop();
        std::cout << "Visited Node Index -> " << node << "\n";

        for (const auto &[nbr, weight] : graph.at(node))
        {
            // loops twice for single edge
            if (!visited[nbr])
            {                
                nodes_stack.emplace(nbr);
                visited[nbr] = 1;
            }
        }
    }

    return 0;
}
