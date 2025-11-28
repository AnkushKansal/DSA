#include <iostream>
#include <vector>
#include <stack>
#include <queue>

//  KAHn's Algo
//  Space : O(nodes)
//  Time : O(V+E)
int main()
{
    // Directed graph adjacency list
    const std::vector<std::vector<int>> graph = {
        {1}, // task 0 is dependent on task 1
        {3},
        {},
        {2, 4}, // task 3 is dependent on task 2 and 4
        {},
    };

    auto size = graph.size();

    std::vector<int> indegree(size, 0);
    // O(V+E)
    for (const auto &edges : graph)
        for (const auto &edge : edges)
            ++indegree[edge];


    std::queue<int> _0_indegree_node_queue;
    for (size_t index = 0; index < indegree.size(); ++index)
        if (indegree[index] == 0)
            _0_indegree_node_queue.push(index);

    //  O(n)
    std::stack<int> task_sequence;
    while (!_0_indegree_node_queue.empty())
    {
        const auto node = _0_indegree_node_queue.front();
        _0_indegree_node_queue.pop();
        task_sequence.emplace(node);

        for (const auto &edge : graph.at(node))
        {
            --indegree[edge];
            if (0 == indegree[edge])
            {
                _0_indegree_node_queue.emplace(edge);
            }
        }
    }

    std::cout << " One Linear ordering of topology is : ";
        while (!task_sequence.empty())
        {
            std::cout << task_sequence.top() << ", ";
            task_sequence.pop();
        }

    return 0;
}
