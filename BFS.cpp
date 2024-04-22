#include "iostream"
#include "vector"
#include "unordered_set"

struct Node {
    int data;
    std::vector<Node *> children;

    Node(int data) : data(data) {}
};

template <typename T>
class LinkedListQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    LinkedListQueue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(T data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    T dequeue() {
        if (isEmpty()) {
            std::cerr << "Queue is empty. Cannot dequeue.\n";
            exit(1);
        }
        T data = front->data;
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return data;
    }

    T peek() {
        if (isEmpty()) {
            std::cerr << "Queue is empty. Cannot peek.\n";
            exit(1);
        }
        return front->data;
    }

    ~LinkedListQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

class Graph {
    std::vector<Node *> nodes;

public:
    Graph(int n) {
        for (int i = 0; i < n; i++) {
            nodes.push_back(new Node(i));
        }
    }

    void addEdge(int parent, int child) {
        nodes[parent]->children.push_back(nodes[child]);
        nodes[child]->children.push_back(nodes[parent]);
    }

    void print() {
        for (int i = 0; i < nodes.size(); i++) {
            std::cout << nodes[i]->data << " -> ";
            for (auto child : nodes[i]->children) {
                std::cout << child->data << " ";
            }
            std::cout << std::endl;
        }
    }

    void bfs() {
        LinkedListQueue<Node *> q;
        std::unordered_set<Node *> visited;

        q.enqueue(nodes[0]);
        visited.insert(nodes[0]);

        while (!q.isEmpty()) {
            Node *front = q.dequeue();
            std::cout << front->data << " ";

            for (auto child : front->children) {
                if (visited.find(child) == visited.end()) {
                    q.enqueue(child);
                    visited.insert(child);
                }
            }
        }
    }

    ~Graph() {
        for (auto node : nodes) {
            delete node;
        }
    }
};

int main() {
    Graph g(10);

    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 7); 
    g.addEdge(2, 9);
    g.addEdge(2, 8); 
    g.addEdge(3, 2);
    g.addEdge(3, 4);
    g.addEdge(5, 3);
    g.addEdge(5, 6);
    g.addEdge(6, 7);

    g.print();
    std::cout << "-------" << std::endl;
    g.bfs();

    return 0;
}
