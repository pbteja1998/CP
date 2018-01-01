#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> iPair;

class Graph
{
    private:
        class Node;    
        int nNodes;        
        vector<Node> Nodes;
        bool DFS(int node, vector<bool> &Visited, int prevNode);
        bool isParallelOrSelfLoop();

    public:
        Graph(int N);
        void addEdge(int src, int dest);    
        bool isCyclePresent();
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

bool Graph::DFS(int node, vector<bool> &Visited, int prevNode)
{
    Visited[node] = true;

    vector<int> :: iterator it;

    for(it = Nodes[node].adj.begin(); it != Nodes[node].adj.end(); it++) {            
        if(Visited[*it] && (*it) != prevNode)
            return true;
        else if(!Visited[*it] && DFS(*it, Visited, node, adj))         
            return true;        
    }

    return false;
}

bool Graph::isParallelOrSelfLoop()
{
    for(int i = 0; i < nNodes; i++) {
        vector<int> :: iterator it;

        unordered_set<int> S;

        for(it = Nodes[i].adj.begin(); it != Nodes[i].adj.end(); it++) {
            if(S.find(*it) != S.end() || *it == i)
                return true;            
            S.insert(*it);
        }
    }

    return false;
}

bool Graph::isCyclePresent()
{
    if(isParallelOrSelfLoop())
        return true;

    vector<bool> Visited(nNodes, false);

    for(int i = 0; i < nNodes; i++) {
        if(!Visited[i]){            
            if(DFS(i, Visited, -1))
                return true;            
        }            
    }

    return false;
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

    cout << G.isCyclePresent() << endl;

    return 0;
}

/**
    Assumptions:
        Graph is Undirected

    Algo:
        If Graph has Parallel Edges or Self-Loops, then the Graph has a cycle
        For every visited vertex ‘v’, 
            if there is an adjacent ‘u’ such that u is already visited and u is not parent of v in DFS Tree generated till then, 
            then there is a cycle in graph

    Complexity:
        O(V+E)
**/