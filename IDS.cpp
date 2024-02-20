#include<bits/stdc++.h>
using namespace std;

// Graph class represents a directed graph using adjacency list representation.
class Graph
{
    int V;  // Number of vertices
    list<int> *adj;  // Pointer to an array containing adjacency lists

    // A function used by IDDFS
    bool DLS(int v, int target, int limit);

public:
    Graph(int V);  // Constructor
    void addEdge(int v, int w);
    bool IDDFS(int src, int target, int max_depth);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

// A function to perform a Depth-Limited search from given source 'src'
bool Graph::DLS(int src, int target, int limit)
{
    if (src == target)
        return true;

    // If reached the maximum depth, stop recursing.
    if (limit <= 0)
        return false;

    // Recur for all the vertices adjacent to the source vertex
    for (auto i = adj[src].begin(); i != adj[src].end(); ++i)
        if (DLS(*i, target, limit-1) == true)
            return true;

    return false;
}

// IDS to search if the target is reachable from v. It uses recursive DFSUtil().
bool Graph::IDDFS(int src, int target, int max_depth)
{
    // Repeatedly depth-limit search till the maximum depth.
    for (int i = 0; i <= max_depth; i++)
        if (DLS(src, target, i) == true)
            return true;

    return false;
}

int main()
{
    int numNodes, numEdges;

    // Get the number of nodes and edges from the user
    cout << "Enter the number of nodes and edges: ";
    cin >> numNodes >> numEdges;

    // Create a graph with the given number of nodes
    Graph g(numNodes);

    // Get the edges from the user
    cout << "Enter the edges (format: source destination): \n";
    for (int i = 0; i < numEdges; i++) {
        int source, destination;
        cin >> source >> destination;
        g.addEdge(source, destination);
    }

    int target, maxDepth, src;

    // Get source, target, and maximum depth from the user
    cout << "Enter the source node: ";
    cin >> src;

    cout << "Enter the target node: ";
    cin >> target;

    cout << "Enter the maximum depth: ";
    cin >> maxDepth;

    // Perform IDS and display the result
    if (g.IDDFS(src, target, maxDepth) == true)
        cout << "Target is reachable from source within max depth";
    else
        cout << "Target is NOT reachable from source within max depth";

    return 0;
}
