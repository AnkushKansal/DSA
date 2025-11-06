#include <unordered_map>
#include <queue>
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

// Cycle in  undirected graph
bool find_cycle_bfs(const auto &root, const auto &graph, auto &visited)
{
    std::queue<std::pair<u_short, u_short>, std::deque<std::pair<u_short, u_short>>> nodes_queue;

    nodes_queue.emplace(root, -1);
    bool is_cycle = false;

    while (!nodes_queue.empty() && !is_cycle)
    {
        auto &[node, parent] = nodes_queue.front();
        nodes_queue.pop();
        std::cout << "Visited Node Index -> " << node << "\n";
        visited[node] += 1;

        for (const auto &edge : graph.at(node))
        {
            if (!visited[edge])
            {
                nodes_queue.emplace(edge, node);
                std::cout << "Visited edge Index -> " << edge << "\n";
                visited[edge] += 1;
            }
            else if (edge != parent)
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

    for (auto &edges_vec : graph)
    {
        for (auto &edge : edges_vec.second)
        {
            if (visited.find(edge) == visited.end())
                visited[edge] = 0;
        }
    }

    static int components = 0;
    for (const auto &[node, is_visited]: visited)
    {
        if (!is_visited)
        {
            ++components;
            if (find_cycle_bfs(node, graph, visited))
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