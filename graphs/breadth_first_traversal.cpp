// Level Wise traversal

#include <queue>
#include "graph_repr_weighted_list.h"

// Undirected Graph/Tree
// Space : O(nodes)
// Time : O(nodes)+O(Total Degree) = O(nodes)+O(2Edges)
int main()
{
    auto graph = get_graph_list();

    std::vector<int> visited(graph.size(), 0);

    u_short root = 0;
    std::cout << "Enter Root Node : ";
    std::cin >> root;

    std::queue<u_short, std::deque<u_short>> nodes_queue;
    nodes_queue.emplace(root);

    while (!nodes_queue.empty())
    {
        u_short &ele = nodes_queue.front();

        if (!visited[ele])
        {
            for (auto &item : graph[ele])
            { // loops twice for single edge
                if (!visited[item.first])
                    nodes_queue.emplace(item.first);
            }
            std::cout << "Visited " << ele << "\n";
            visited[ele] = 1;
        }
        nodes_queue.pop();
    }
}
