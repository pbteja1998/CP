#include<bits/stdc++.h>
using namespace std;

class Graph
{
    private:
        int nNodes;
        class Node;
        class AdjNode;        
        vector<Node> Nodes;
        void Dijkstra(vector<int> &distNodes);
        int getMinIndex(vector<bool> finishedSet, vector<int> distNodes);

    public:
        Graph(int V);
        void addEdge(int src, int dest, int weight);
        void printShortestDistances(int src);     
};

class Graph::AdjNode
{
    public:
        int dest;
        int weight;
        AdjNode(int d, int w)
        {
            dest = d;
            weight = w;
        }    
};

class Graph::Node
{    
    public:
        vector<AdjNode> adj;

        void addAdjNode(int dest, int weight)
        {
            AdjNode n(dest, weight);
            adj.push_back(n);        
        }
};

Graph::Graph(int V)
{
    nNodes = V;

    for(int i = 0; i < nNodes; i++) {
        Node n;
        Nodes.push_back(n);
    }
}

void Graph::addEdge(int src, int dest, int weight)
{
    Nodes[src].addAdjNode(dest, weight);
}

int Graph::getMinIndex(vector<bool> finishedSet, vector<int> distNodes)
{
    int min_value = INT_MAX, min_index = -1;

    for(int i = 0; i < nNodes; i++) {
        if(!finishedSet[i]){
            if(distNodes[i] < min_value){
                min_value = distNodes[i];
                min_index = i;
            }                
        }            
    }

    return min_index;
}

void Graph::Dijkstra(vector<int> &distNodes)
{
    vector<bool> finishedSet(nNodes, false);    

    for(int i = 0; i < nNodes - 1; i++) {
        int min_index = getMinIndex(finishedSet, distNodes);
        finishedSet[min_index] = true;

        vector<AdjNode> :: iterator it;
        for(it = Nodes[min_index].adj.begin(); it != Nodes[min_index].adj.end(); it++) {
            int dest = (*it).dest;
            int weight = (*it).weight;

            if(!finishedSet[dest]) {
                if(distNodes[min_index] + weight < distNodes[dest])
                    distNodes[dest] = distNodes[min_index] + weight;
            }
        }
    }    
}

void Graph::printShortestDistances(int src)
{
    vector<int> distNodes(nNodes, INT_MAX);
    distNodes[src] = 0;

    Dijkstra(distNodes);

    for(int i = 0; i < nNodes; i++) {
        cout << "shortest distance from " << src << " to " << i << " is " << distNodes[i] << endl;
    }
}

int main()
{
    int nNodes, nEdges;
    cin >> nNodes >> nEdges;

    Graph G(nNodes);

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
    Assumptions:        
        There are no negative edges.        

    Complexity:
        O(V*V)
        Can be reduced to O(ElogV)

    Sample Test Case
    Input:
        5 8
        0 1 2
        0 2 7
        1 2 6
        1 3 5
        1 4 5
        3 2 8
        3 1 4
        4 3 0
        0
    Output:
        shortest distance from 0 to 0 is 0
        shortest distance from 0 to 1 is 2
        shortest distance from 0 to 2 is 7
        shortest distance from 0 to 3 is 7
        shortest distance from 0 to 4 is 7
**/