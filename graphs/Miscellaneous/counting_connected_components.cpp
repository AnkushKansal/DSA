#include <unordered_map>
#include <stack>

#include "../Graph_representation/graph_repr_weighted_list.h"

void depth_first_traversal(auto &root, auto &graph, auto &visited)
{
    std::cout << "Visited Node Index -> " << root << "\n";
    visited[root] = 1;

    for (const auto &[edge, weight] : graph.at(root))
    {
        // loops twice for single edge
        if (!visited[edge])
        {
            depth_first_traversal(edge, graph, visited);
        }
    }
}

// Undirected Graph/Tree
// Space : O(nodes)
// Time : O(nodes + 2edges)
// O(nodes)for visited map + O(nodes) for outer loop + (O(nodes)+ O(2Edges) for DFS
int main()
{
    const auto graph = get_graph_list(); // sparse graph

    std::unordered_map<u_short, short> visited;
    for (auto &[parent, edges] : graph)
    {
        for (auto &[edge, weight] : edges)
        {
            if (visited.find(edge) == visited.end())
                visited[edge] = 0;
        }
    }

    short compo_count = 0;

    for (auto &[node, is_visited] : visited)
    {
        if (!is_visited)
        {
            depth_first_traversal(node, graph, visited);
            ++compo_count;
        }
    }

    std::cout << "Total components in given graph : " << compo_count << "\n";
    return 0;
}