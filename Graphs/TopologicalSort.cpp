#include<bits/stdc++.h>
using namespace std;

/**
Assumptions:
- Graph is Directed and Acyclic
**/

class Graph
{
    class Node;    
    int nNodes;

    public:
    vector<Node> Nodes;
    Graph(int N);
    void addEdge(int src, int dest);
    void DFS(int node, vector<bool> &Visited, stack<int> &SortedStack);
    stack<int> getTopologicalSorting();
    void printTopologicallySortedStack();
};

class Graph::Node
{    
    public:
    //add any other related parameters that are specific to a node
    vector<int> adj;
    Node(){}
};

Graph::Graph(int N)
{
    nNodes = N;

    for(int i = 0; i < N; i++){
        Node n;
        Nodes.push_back(n);
    }
}

void Graph::addEdge(int src, int dest)
{
    Nodes[src].adj.push_back(dest);
}

void Graph::DFS(int node, vector<bool> &Visited, stack<int> &SortedStack)
{
    Visited[node] = true;

    vector<int> :: iterator it;

    for(it = Nodes[node].adj.begin(); it != Nodes[node].adj.end(); it++) {
        if(!Visited[*it])
            DFS(*it, Visited, SortedStack);
    }

    SortedStack.push(node);
}

stack<int> Graph::getTopologicalSorting()
{
    stack<int> SortedStack;

    vector<bool> Visited(nNodes, false);

    for(int i = 0; i < nNodes; i++) {
        if(!Visited[i])
            DFS(i, Visited, SortedStack);
    }

    return SortedStack;
}

void Graph::printTopologicallySortedStack()
{
    stack<int> SortedStack = getTopologicalSorting();

    while(!SortedStack.empty()) {
        cout << SortedStack.top() << " ";
        SortedStack.pop();
    }
}

int main()
{
    int nNodes, nEdges;
    cin >> nNodes >> nEdges;

    Graph G(nNodes);

    int u, v;        

    while(nEdges--) {
        cin >> u >> v;
        G.addEdge(u, v);        
    }        
        
    G.printTopologicallySortedStack();

    return 0;
}

/**
    Algo:
        During DFS, the node with higher finishing time is more to the left and vice-versa
        Finishing time of a node N is time taken to finish visiting all the children of N;

    Complexity:
        O(V+E)
**/