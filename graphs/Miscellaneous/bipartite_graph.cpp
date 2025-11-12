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