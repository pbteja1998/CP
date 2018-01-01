#include<bits/stdc++.h>
using namespace std;

class Graph
{
    private:
        class Node;    
        int nNodes;
        vector<Node> Nodes;
        void DFS(int node, vector<bool> &Visited);
        void BFS(int node, vector<bool> &Visited);

    public:    
        Graph(int N);
        void addEdge(int src, int dest);
        int nConnectedComponents();
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

void Graph::DFS(int node, vector<bool> &Visited)
{
    //visit(node);
    Visited[node] = true;

    vector<int> :: iterator it;

    for(it = Nodes[node].adj.begin(); it != Nodes[node].adj.end(); it++){
        if(!Visited[*it])
            DFS(*it, Visited);
    }
}

void Graph::BFS(int node, vector<bool> &Visited)
{
    //visit(node);
    Visited[node] = true;

    queue<int> Q;
    Q.push(node);

    while(!Q.empty())
    {
        int currentNode = Q.front();
        //visit(currentNode);
        Q.pop();
        vector<int> :: iterator it;

        for(it = Nodes[currentNode].adj.begin(); it != Nodes[currentNode].adj.end(); it++) {
            if(!Visited[*it]){
                Visited[*it] = true;
                Q.push(*it);
            }                
        }   
    }
}

int Graph::nConnectedComponents()
{
    vector<bool> Visited(nNodes, 0);

    int ans = 0;

    for(int j = 0; j < nNodes; j++) {
        if(!Visited[j]){
            // DFS(j, Visited);
            BFS(j, Visited);
            ans++;
        }                
    }

    return ans;
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
        
    cout << G.nConnectedComponents() << endl;

    return 0;
}

/**
    Complexity:
        DFS: O(V+E)
        BFS: O(V+E)
**/