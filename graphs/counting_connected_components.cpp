#include <unordered_map>
#include <stack>

#include "graph_repr_weighted_list.h"

void depth_first_traversal(const auto &root, const auto &graph, auto &visited)
{
    std::stack<u_short, std::deque<u_short>> nodes_stack;
    nodes_stack.emplace(root);
    std::cout << "Visited Node Index -> " << root << "\n";
    visited[root] = 1;

    while (!nodes_stack.empty())
    {
        u_short ele = nodes_stack.top();
        nodes_stack.pop();

        for (auto &edges : graph.at(ele))
        {
            // loops twice for single edge
            if (!visited[edges.first])
            {
                nodes_stack.emplace(edges.first);
                std::cout << "Visited Node Index -> " << edges.first << "\n";
                visited[edges.first] = 1;
            }
        }
    }
}

// Undirected Graph/Tree
// Space : O(nodes)
// Time : O(nodes + 2edges)
// O(nodes)for visited map + O(nodes) for outer loop + (O(nodes)+ O(2Edges) for DFS
int main()
{
    auto graph = get_graph_list(); // sparse graph

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