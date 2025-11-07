#include <unordered_map>
#include <stack>
#include <vector>
#include <iostream>

auto get_graph_list()
{
    u_short nodes, edges;

    std::cout << "Enter number of nodes and edges in a graph" << "\n";
    std::cin >> nodes >> edges;

    // Used map as indices could be sparse for the graph. Not cache friendly
    std::unordered_map<u_short, std::vector<u_short>> adjlist;

    int uend, vend, edge_weight;
    for (auto i = 0U; i < edges; i++)
    {
        std::cout << " Enter edge : ";
        std::cin >> uend >> vend;

        adjlist[uend].emplace_back(vend);
        adjlist[vend].emplace_back(uend);
    }
    return adjlist;
}

// Cycle in  undirected graph using depth traversal
bool find_cycle_dfs(const auto &root, const auto &graph, auto &visited)
{
    std::stack<std::pair<u_short, u_short>, std::deque<std::pair<u_short, u_short>>> nodes_stack;
    nodes_stack.emplace(root, -1);
    visited[root] = 1;

    bool is_cycle = false;

    while (!nodes_stack.empty() && !is_cycle)
    {
        auto [node, parent] = nodes_stack.top();
        nodes_stack.pop();
        std::cout << "Visited Node Index -> " << node << "\n";

        for (const auto &nbr : graph.at(node))
        {
            if (!visited[nbr])
            {
                nodes_stack.emplace(nbr, node);
                visited[nbr] = 1;
            }
            else if (nbr != parent)
                is_cycle = true;
        }
    }
    return is_cycle;
}

// Undirected Graph/Tree
// Space : O(nodes)
// Time : O(nodes + 2edges)
// O(nodes)for visited map + O(nodes) for outer loop + (O(nodes)+ O(2Edges) for DFS
int main()
{
    auto graph = get_graph_list();

    std::unordered_map<u_short, short> visited;
    for (auto &[nodes, edges] : graph)
    {
        for (auto &edge : edges)
        {
            if (visited.find(edge) == visited.end())
                visited[edge] = 0;
        }
    }

    static int components = 0;
    for (const auto &[node, is_visited] : visited)
    {
        if (!is_visited)
        {
            ++components;
            if (find_cycle_dfs(node, graph, visited))
            {
                std::cout << " Cycle detected in component " << components << "\n";
                break;
            }
            else
                std::cout << " No Cycle detected in component " << components << "\n";
        }
    }
    return 0;
}