// Level Wise traversal

#include <cassert>
#include <queue>
#include <ranges>
#include <algorithm>
#include <unordered_map>

#include "graph_repr_weighted_list.h"

// Undirected Graph/Tree
// Space : O(nodes)
// Time : O(nodes + 2*edges)  //(O(nodes) for visited map + (O(nodes)+ O(2Edges))
int main()
{
    auto graph = get_graph_list();

    std::unordered_map<u_short, short> visited;
    for (auto &edges_vec : graph)
    {
        for (auto &edge : edges_vec.second)
        {
            visited[edge.first] = 0;
        }
    }

    u_short root = 1;
    std::cout << "Enter Root Node : ";
    std::cin >> root;
    auto min_max_it = std::ranges::minmax_element(visited, std::less<>(), &decltype(visited)::value_type::first); // compare by key
    assert(min_max_it.min != visited.end() && min_max_it.max != visited.end());
    assert(root <= min_max_it.max->first && root >= min_max_it.min->first);

    std::queue<u_short, std::deque<u_short>> nodes_queue;
    nodes_queue.emplace(root);
    visited[root] = 1;
    std::cout << "Visited Node Index -> " << root << "\n";

    while (!nodes_queue.empty())
    {
        u_short ele = nodes_queue.front();
        nodes_queue.pop();

        for (auto &edges : graph.at(ele))
        {
            // loops twice for single edge
            if (!visited[edges.first])
            {
                nodes_queue.emplace(edges.first);
                visited[edges.first] = 1;
                std::cout << "Visited Node Index -> " << edges.first << "\n";
            }
        }
    }
}
