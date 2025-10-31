#include <iostream>
#include <vector>

//Time : O(edges), Space = O(2*edges)
int main(){

    unsigned nodes, edges;
    
    std::cout << "Enter number of nodes and edges in a graph" << "\n";    
    std::cin >> nodes >> edges;

    std::vector<std::vector<std::pair<unsigned,signed>>> adjlist(nodes+1);

    int uend, vend, edge_weight;
    for (auto i = 0; i < edges; i++){

        std::cout << " Enter  weighted edge : ";
        std::cin >> uend >> vend >> edge_weight;

        adjlist[uend].emplace_back(std::make_pair(vend, edge_weight));
        adjlist[vend].emplace_back(std::make_pair(uend, edge_weight));
    }
    return 0;
}

