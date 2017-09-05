/*graph.h*/

#pragma once

#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;

class Graph
{
    private:
    class Edge
    {
        public:
        int   Src, Dest, Weight;
        Edge *Next;
    };

    Edge  **Vertices;
    string *Names;
    int     NumVertices;
    int     NumEdges;
    int     Capacity;

    int FindVertexByName(string name);
    vector<int> iNeighbors(int v);

    public:

    // Constructor
    Graph(int N);
    // Destructor
    ~Graph();

    // Graph debugging functions
    void PrintGraph(string title);

    // Graph boolean functions
    bool EdgeExists(string src, string dest);

    // Graph modification functions
    bool AddVertex(string v);
    bool AddEdge(string src, string dest, int weight);
    void UpdateEdge(string src, string dest);

    // Getter functions
    int GetNumVertices();
    int GetNumEdges();
    int GetWeight(string src, string dest);
    set<string> GetVertices();
    set<string> GetNeighbors(string v);
    vector<int> GetEdgeWeights(string src, string dest);

    // Graph searching functions
    vector<string> BFS(string v);
};
