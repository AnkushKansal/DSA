#include <iostream>
#include <vector>
#include <cassert>

// Time : O(edges) , Space:  O(nodes*nodes)
auto get_graph_matrix()
{
    int nodes, edges;

    std::cout << "Enter number of nodes and edges in a graph" << "\n";
    std::cin >> nodes >> edges;

    std::vector<std::vector<int>> adjmat(nodes + 1, std::vector<int>(nodes + 1, 0)); //  +1 so that node indices can start from 1 instead of 0

    int uend, vend;
    for (size_t i = 0; i < edges; ++i)
    {
        std::cout << " Enter  edge : ";
        std::cin >> uend >> vend;
        assert(uend <= nodes && vend <= nodes && uend >= 0 && vend >= 0);

        // As graph is undirected, an edge is present between a pair of node
        adjmat[uend][vend] = 1;
        adjmat[vend][uend] = 1;
    }
    return adjmat;
}