#include<bits/stdc++.h>
using namespace std;

class Graph
{
    private:
    class Node;    
    int nNodes;
    stack<int> SortAsPerFinishingTimes();
    void fillSortedStack(int node, vector<bool> &Visited, stack<int> &SortedStack);
    void DFS(int node, vector<bool> &Visited, vector<int> &Component);
    vector<vector<int>> getStronglyConnectedComponents(Graph G);

    public:
    vector<Node> Nodes;
    Graph(int N);
    void addEdge(int src, int dest);
    void printStronglyConnectedComponents(Graph G);
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

stack<int> Graph::SortAsPerFinishingTimes()
{
    stack<int> SortedStack;

    vector<bool> Visited(nNodes, false);

    for(int i = 0; i < nNodes; i++) {
        if(!Visited[i])
            fillSortedStack(i, Visited, SortedStack);
    }

    return SortedStack;
}

void Graph::fillSortedStack(int node, vector<bool> &Visited, stack<int> &SortedStack)
{
    Visited[node] = true;

    vector<int> :: iterator it;

    for(it = Nodes[node].adj.begin(); it != Nodes[node].adj.end(); it++) {
        if(!Visited[*it])
            fillSortedStack(*it, Visited, SortedStack);
    }

    SortedStack.push(node);
}

void Graph::DFS(int node, vector<bool> &Visited, vector<int> &Component)
{
    //visit(node);
    Visited[node] = true;

    Component.push_back(node);

    vector<int> :: iterator it;

    for(it = Nodes[node].adj.begin(); it != Nodes[node].adj.end(); it++){
        if(!Visited[*it])
            DFS(*it, Visited, Component);
    }
}

vector<vector<int>> Graph::getStronglyConnectedComponents(Graph G)
{
    stack<int> SortedNodes = G.SortAsPerFinishingTimes();

    vector<bool> Visited(nNodes, false);

    vector<int> Component;

    vector<vector<int>> Components;

    while(!SortedNodes.empty()) {
        int topNode = SortedNodes.top();
        SortedNodes.pop();
        Component.clear();
        if(!Visited[topNode]){
            DFS(topNode, Visited, Component);
            Components.push_back(Component);
        }            
    }

    return Components;
}

void Graph::printStronglyConnectedComponents(Graph G)
{
    vector<vector<int>> Components = getStronglyConnectedComponents(G);

    for(int i = 0; i < Components.size(); i++) {
        for(int j = 0; j < Components[i].size(); j++)
            cout << Components[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    int nNodes, nEdges;
    cin >> nNodes >> nEdges;

    Graph G(nNodes);
    Graph GT(nNodes);

    int u, v;        

    while(nEdges--) {
        cin >> u >> v;
        G.addEdge(u, v);
        GT.addEdge(v, u);
    }    

    GT.printStronglyConnectedComponents(G);

    return 0;
}

/**
    Assumptions:
        Graph is Directed
        
    Algo:
        Do DFS on G and sort the nodes in the ascending order as per the finishing times
        Finishing time of a node N is time taken to finish visiting all the children of N;
        Do DFS in the order obtained above on G-Transpose,
            each DFS Forest thus obtained is a Strongly Connected Component

    Complexity:
        O(V+E)
**/