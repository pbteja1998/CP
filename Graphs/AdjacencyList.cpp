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

int main()
{
    return 0;
}