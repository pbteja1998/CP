#include<bits/stdc++.h>
using namespace std;

class Graph
{
    private:
        class Node;    
        int nNodes;
        void DFS(int node, vector<bool> &Visited, bool &isCycle, int &prevNode);
        vector<Node> Nodes;

    public:
        Graph(int N);
        void addEdge(int src, int dest);    
        bool isCyclePresent();
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

void Graph::DFS(int node, vector<bool> &Visited, bool &isCycle, int &prevNode)
{
    Visited[node] = true;

    vector<int> :: iterator it;

    for(it = Nodes[node].adj.begin(); it != Nodes[node].adj.end(); it++) {
        if(Visited[*it] && (*it) != prevNode) {            
            isCycle = true;
            return;
        } else if(!Visited[*it]){
            prevNode = node;
            DFS(*it, Visited, isCycle, prevNode);   
        }            
    }
}

bool Graph::isCyclePresent()
{
    vector<bool> Visited(nNodes, false);

    bool isCycle = false;
    int prevNode;

    for(int i = 0; i < nNodes; i++) {
        if(!Visited[i]){
            prevNode = -1;
            DFS(i, Visited, isCycle, prevNode);            
            if(isCycle)
                return true;
        }            
    }

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
        G.addEdge(v, u);
    }        
        
    cout << G.isCyclePresent() << endl;

    return 0;
}

/**
    Assumptions:
        Graph is Undirected and has No Parallel Edges        

    Algo:
        For every visited vertex ‘v’, 
            if there is an adjacent ‘u’ such that u is already visited and u is not parent of v in DFS Tree generated till then, 
            then there is a cycle in graph

    Complexity:
        O(V+E)
**/