#include <iostream>
#include <vector>
#include <unordered_map>

//Time : O(edges), Space = O(2*edges)
auto get_graph_list(){

    u_short nodes, edges;
    
    std::cout << "Enter number of nodes and edges in a graph" << "\n";    
    std::cin >> nodes >> edges;

    //Used map as indices could be sparse for the graph. Not cache friendly
    std::unordered_map<u_short, std::vector<std::pair<u_short,short>>> adjlist(nodes+1);

    int uend, vend, edge_weight;
    for (auto i = 0U; i < edges; i++){

        std::cout << " Enter edge and their weight : ";
        std::cin >> uend >> vend >> edge_weight;

        adjlist[uend].emplace_back(std::make_pair(vend, edge_weight));
        adjlist[vend].emplace_back(std::make_pair(uend, edge_weight));
    }
    return adjlist;
}