#include <iostream>
#include <vector>


//Time : O(m) , Space O(n*n)
int main(){

    int nodes, edges;
    
    std::cout << "Enter number of nodes and edges in a graph" << "\n";    
    std::cin >> nodes >> edges;

    std::vector<std::vector<int>> adjmat (nodes+1, std::vector<int> (nodes+1, 0)); // +1 because index  start from 0

    int uend, vend;
    for (auto i = 0; i < edges; ++i)
    {
        std::cout << " Enter  edge : ";
        std::cin >> uend >> vend;
        
        //As graph is undirected, an edge is present between a pair of node
        adjmat[uend][vend] = 1;
        adjmat[vend][uend] = 1;
    }

    return 0;
}