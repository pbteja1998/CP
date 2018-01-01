#include<bits/stdc++.h>
using namespace std;

class Graph
{
    private:
        class Node;    
        int nNodes;
        bool DFS(int node, vector<bool> &Visited, vector<bool> &recStack);
        vector<Node> Nodes;

    public:
        Graph(int N);
        void addEdge(int src, int dest);    
        bool isCyclic();
        void printAdjacencyList();
};

class Graph::Node
{    
    public:    
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

void Graph::printAdjacencyList()
{
    for(int i = 0; i < nNodes; i++) {
        cout << i << " : ";
        for(int j = 0; j < Nodes[i].adj.size(); j++)
            cout << Nodes[i].adj[j] << " ";        
        cout << endl;
    }
}

bool Graph::isCyclic()
{
    vector<bool> Visited(nNodes, false);
    vector<bool> recStack(nNodes, false);

    for(int i = 0; i < nNodes; i++) {
        if(!Visited[i]){
            if(DFS(i, Visited, recStack))
                return true;            
        }            
    }

    return false;
}

bool Graph::DFS(int node, vector<bool> &Visited, vector<bool> &recStack)
{
    Visited[node] = true;
    recStack[node] = true;

    vector<int> :: iterator it;

    for(it = Nodes[node].adj.begin(); it != Nodes[node].adj.end(); it++) {
        if(!Visited[*it] && DFS(*it, Visited, recStack))
            return true;
        else if(recStack[*it])
            return true;              
    }

    recStack[node] = false;

    return false;
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
        
    cout << G.isCyclic() << endl;

    return 0;
}

/**
    Assumptions:
        Graph is Directed

    Algo:
        If there is a back edge, then there is a cycle.
        During DFS, if you visit a visited vertex such that it is already present in the DFS Tree generated till then,
        it means that there is a back edge.

    Complexity:
        O(V+E)
**/