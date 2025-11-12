#include <unordered_map>
#include <queue>
#include <iostream>
#include <cassert>
#include <string>
auto get_graph_list()
{
    int nodes, edges;

    std::cout << "Enter number of nodes and edges in a graph" << "\n";
    std::cin >> nodes >> edges;

    // dense graph
    std::vector<std::vector<int>> graph(nodes + 1); //  +1 so that node indices can start from 1 instead of 0

    int uend, vend;
    for (auto i = 0; i < edges; ++i)
    {
        std::cout << " Enter  edge : ";
        std::cin >> uend >> vend;
        assert(uend >= 1 && uend <= nodes && vend <= nodes && vend >= 1);

        // As graph is undirected, an edge is present between a pair of node
        graph[uend].emplace_back(vend);
        graph[vend].emplace_back(uend);
    }
    return graph;
}

bool check_bipartite(const auto start, const auto &graph, auto &visited)
{
    bool if_bipartite = true;
    std::queue<int, std::deque<int>> nodes_queue;
    nodes_queue.emplace(start);
    visited[start] = "Red";

    while (!nodes_queue.empty())
    {
        auto node = nodes_queue.front();
        nodes_queue.pop();
        std::cout << "Visited node :" << node << ", Color :" << visited[node] << "\n";

        for (auto &nbr : graph[node])
        {
            if (visited[nbr] == "None")
            {
                nodes_queue.emplace(nbr);
                visited[node] == "Red" ? visited[nbr] = "Blue" : visited[nbr] = "Red";
            }

            else if (visited[nbr] == visited[node])
            {
                if_bipartite = false;
                break;
            }
        }
    }

    return if_bipartite;
}

int main()
{

    auto graph = get_graph_list();

    auto size = graph.size();
    std::vector<std::string> visited(size, "None");

    auto if_bipartite = true;

    for (size_t index = 1; index < visited.size(); ++index)
    {
        if (visited[index] == "None")
        {
            if_bipartite = check_bipartite(1, graph, visited);
            if (!if_bipartite)
                break;
        }
    }

    std::cout << " Graph is bipartite " << std::boolalpha << if_bipartite << "\n";

    return 0;
}