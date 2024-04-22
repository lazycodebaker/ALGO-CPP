#include <iostream>
#include <vector>
#include <stack>

class Graph
{
public:
    struct Node
    {
        int data;
        std::vector<Node *> neighbors;

        Node(int val) : data(val) {}
    };

    void addEdge(Node *u, Node *v)
    {
        u->neighbors.push_back(v);
        v->neighbors.push_back(u);  
    }

    void DFS(Node *start)
    {
        std::stack<Node *> stack;
        stack.push(start);

        while (!stack.empty())
        {
            Node *current = stack.top();
            stack.pop();

            if (!visited[current])
            {
                visited[current] = true;
                processNode(current);

                for (Node *neighbor : current->neighbors)
                {
                    if (!visited[neighbor])
                    {
                        stack.push(neighbor);
                    }
                }
            }
        }
    }

private:
    std::unordered_map<Node *, bool> visited;

    void processNode(Node *node)
    {
        std::cout << "Visited node with data: " << node->data << std::endl;
    };
};

int main()
{
    Graph graph;

    Graph::Node *node1 = new Graph::Node(1);
    Graph::Node *node2 = new Graph::Node(2);
    Graph::Node *node3 = new Graph::Node(3);
    Graph::Node *node4 = new Graph::Node(4);
    Graph::Node *node5 = new Graph::Node(5);

    graph.addEdge(node1, node2);
    graph.addEdge(node1, node3);
    graph.addEdge(node2, node4);
    graph.addEdge(node3, node4);
    graph.addEdge(node4, node5);

    graph.DFS(node1);

    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;

    return 0;
}
