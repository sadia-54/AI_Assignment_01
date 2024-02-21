// reg: 2020831054
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//representing a node in the tree
struct Node {
    int data;
    vector<Node*> children;

    Node(int val) : data(val) {}
};

// DLS
Node* dls(Node* root, int target, int depthLimit) {
    stack<pair<Node*, int>> s;
    s.push({root, 0});

    while (!s.empty()) {
        auto current = s.top().first;
        auto depth = s.top().second;
        s.pop();

        cout << "DLS - Visiting Node: " << current->data << " at Depth: " << depth << endl;

        if (current->data == target) {
            cout << "DLS - Target found!" << endl;
            return current;
        }

        if (depth < depthLimit) {
            // Push children to stack in reverse order
            for (int i = current->children.size() - 1; i >= 0; --i) {
                s.push({current->children[i], depth + 1});
            }
        }
    }

    cout << "DLS - Target not found within depth limit." << endl;
    return nullptr;
}

// DFS
Node* dfs(Node* root, int target) {
    stack<Node*> s;
    s.push(root);

    while (!s.empty()) {
        auto current = s.top();
        s.pop();

        cout << "DFS - Visiting Node: " << current->data << endl;

        if (current->data == target) {
            cout << "DFS - Target found!" << endl;
            return current;
        }

        // Push children to stack in reverse order
        for (int i = current->children.size() - 1; i >= 0; --i) {
            s.push(current->children[i]);
        }
    }

    cout << "DFS - Target not found." << endl;
    return nullptr;
}

int main() {
    int numNodes, target, depthLimit;

    // Get the number of nodes in the tree
    cout << "Enter the number of nodes in the tree: ";
    cin >> numNodes;

    // Create nodes
    vector<Node*> nodes;
    for (int i = 1; i <= numNodes; ++i) {
        nodes.push_back(new Node(i));
    }

    // tree structure
    cout << "Enter the tree structure (parent child) - enter -1 to stop:" << endl;
    int parent, child;
    while (cin >> parent && parent != -1 && cin >> child && child != -1) {
        nodes[parent - 1]->children.push_back(nodes[child - 1]);
    }

    //target node
    cout << "Enter the target node: ";
    cin >> target;

    //depth limit
    cout << "Enter the depth limit: ";
    cin >> depthLimit;

    Node* root = nodes[0];

    cout << "\nDepth-Limited Search (DLS):" << endl;
    Node* resultDLS = dls(root, target, depthLimit);

    if (resultDLS) {
        cout << "Node with value " << target << " found within depth limit." << endl;
    } else {
        cout << "Node with value " << target << " not found within depth limit." << endl;
    }

    cout << "\nDepth-First Search (DFS):" << endl;
    Node* resultDFS = dfs(root, target);

    if (resultDFS) {
        cout << "Node with value " << target << " found." << endl;
    } else {
        cout << "Node with value " << target << " not found." << endl;
    }

    // Clean up memory
    for (Node* node : nodes) {
        delete node;
    }

    return 0;
}
