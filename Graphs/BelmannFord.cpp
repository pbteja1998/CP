#include<bits/stdc++.h>
using namespace std;

class Graph
{   
    private:
        int nNodes, nEdges;
        class Edge;
        vector<Edge> Edges;    
        vector<int> distNodes;
        void initDistNodes(int src);
        int BelmannFord(int src);

    public:
        Graph(int V, int E);
        void addEdge(int src, int dest, int weight); 
        void printShortestDistances(int src); 
};

Graph::Graph(int V, int E)
{
    nNodes = V;
    nEdges = E;
}

class Graph::Edge
{
    public:
        int src, dest, weight;

        Edge(int u, int v, int w)
        {
            src = u;
            dest = v;
            weight = w;
        }
};

void Graph::addEdge(int src, int dest, int weight)
{
    Edge E(src, dest, weight);
    Edges.push_back(E);
}

void Graph::initDistNodes(int src)
{
    for(int i = 0; i < nNodes; i++) {
        distNodes.push_back(INT_MAX);
    }    

    distNodes[src] = 0;
}

int Graph::BelmannFord(int src)
{
    initDistNodes(src);

    for(int i = 1; i < nNodes; i++) {
        for(int j = 0; j < nEdges; j++) {
            int src = Edges[j].src;
            int dest = Edges[j].dest;
            int weight = Edges[j].weight;
            if(distNodes[src] != INT_MAX){                
                if(distNodes[src] + weight < distNodes[dest])
                    distNodes[dest] = distNodes[src] + weight;
            }
        }
    }

    for(int j = 0; j < nEdges; j++) {
        int src = Edges[j].src;
        int dest = Edges[j].dest;
        int weight = Edges[j].weight;
        if(distNodes[src] != INT_MAX){        
            if(distNodes[src] + weight < distNodes[dest]){
                cout << "Given Graph has negative cycle" << endl;
                return -1;                
            }                
        }
    }

    return 0;
}

void Graph::printShortestDistances(int src)
{
    if(BelmannFord(src) == 0){
        for(int i = 0; i < nNodes; i++) {
            cout << "shortest distance from " << src << " to " << i << " is " << distNodes[i] << endl;
        }
    }    
}

int main()
{
    int nNodes, nEdges;
    cin >> nNodes >> nEdges;

    Graph G(nNodes, nEdges);

    int u, v, w;

    for(int i = 0; i < nEdges; i++) {
        cin >> u >> v >> w;
        G.addEdge(u, v, w);
    }

    int src;
    cin >> src;
    G.printShortestDistances(src);

    return 0;
}

/**
    Complexity:
        O(VE)

    Sample Test Case
    Input:
        5 8
        0 1 -1
        0 2 4
        1 2 3
        1 3 2
        1 4 2
        3 2 5
        3 1 1
        4 3 -3
        0
    Output:
    shortest distance from 0 to 0 is 0
    shortest distance from 0 to 1 is -1
    shortest distance from 0 to 2 is 2
    shortest distance from 0 to 3 is -2
    shortest distance from 0 to 4 is 1
**/