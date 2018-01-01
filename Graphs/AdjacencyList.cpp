#include<bits/stdc++.h>
using namespace std;

class Graph
{
    private:
        class Node;    
        int nNodes;
        vector<Node> Nodes;

    public:
        Graph(int N);
        void addEdge(int src, int dest);
        void printAdjacencyList(); 
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

void Graph::printAdjacencyList()
{
    for(int i = 0; i < nNodes; i++) {
        cout << i << " : ";
        for(int j = 0; j < Nodes[i].adj.size(); j++)
            cout << Nodes[i].adj[j] << " ";        
        cout << endl;
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
        G.addEdge(v, u);
    }        
        
    G.printAdjacencyList();

    return 0;
}