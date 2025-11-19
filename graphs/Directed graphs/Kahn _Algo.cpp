#include <iostream>
#include <vector>
#include <queue>

//  KAHn's Algo
//  Space : O(nodes)
//  Time : O(V+E)
int main()
{
    // Directed graph adjacency list
    const std::vector<std::vector<int>> graph = {
        {},
        {},
        {3},
        {1},
        {0, 1},
        {0, 2},
    };
    auto size = graph.size();

    std::vector<int> indegree(size, 0);
    // O(V+E)
    for (const auto &edges : graph)
    {
        {
            for (const auto &edge : edges)
            {
                ++indegree[edge];
            }
        }
    }

    std::queue<int> _0_indegree_node_queue;
    for (size_t index = 0; index < indegree.size(); ++index)
    {
        if (indegree[index] == 0)
            _0_indegree_node_queue.push(index);
    }

    std::cout << " One Linear ordering of topology is : ";
    // O(n)
    while (!_0_indegree_node_queue.empty())
    {
        const auto node = _0_indegree_node_queue.front();
        _0_indegree_node_queue.pop();
        std::cout << node << ", ";

        for (const auto &edge : graph.at(node))
        {
            --indegree[edge];
            if (0 == indegree[edge])
            {
                _0_indegree_node_queue.emplace(edge);
            }
        }
    }

    return 0;
}
