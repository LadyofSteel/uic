/*graph.cpp*/

#include <iostream>

#include "graph.h"

using namespace std;


//
// Constructor:
//
Graph::Graph(int N)
{
    this->NumVertices = 0;
    this->NumEdges = 0;
    this->Capacity = N;

    this->Vertices = new Edge*[N];
    this->Names = new string[N];
}


//
// Destructor:
//
Graph::~Graph()
{
    //
    // Future work:
    //
}


//
// PrintGraph:
//
// Prints the graph, typically for debugging purposes.
//
void Graph::PrintGraph(string title)
{
    cout << ">>Graph: " << title << endl;
    cout << "  # of vertices: " << this->NumVertices << endl;
    cout << "  # of edges:    " << this->NumEdges << endl;
    cout << "  Capacity:      " << this->Capacity << endl;

    cout << "  Vertices:" << endl;

    for (int v = 0; v < this->NumVertices; ++v)
    {
        cout << "    " << v << " (" << this->Names[v] << "): ";

        Edge *edge = this->Vertices[v];
        while (edge != nullptr)
        {
            cout << "(" << edge->Src << "," << edge->Dest << "," << edge->Weight << ")";

            edge = edge->Next;
            if (edge != nullptr)
                cout << ", ";
        }

        cout << endl;
    }
}


//
// GetNumVertices:
// Returns the number of vertices in the graph
//
int Graph::GetNumVertices()
{
    return this->NumVertices;
}


//
// GetNumEdges:
// Returns the number of edges in the graph
//
int Graph::GetNumEdges()
{
    return this->NumEdges;
}


//
// FindVertexByName:
// Helper function to find a vertex by name by
// searching the Names array using linear search.
// Returns vertex # (i.e. array index) or -1 if 
// not found
//
int Graph::FindVertexByName(string name)
{
    int index = -1;
    for (int i = 0; i < this->NumVertices; i++)
    {
        if (this->Names[i] == name)
        {
            index = i;
            break;
        }
    }

    return index;
}


//
// EdgeExists:
// Returns true if an edge from src to dest already
// exists in the graph, returns false otherwise.
//
bool Graph::EdgeExists(string src, string dest)
{   
    int s = this->FindVertexByName(src);
    int d = this->FindVertexByName(dest);
    if (s < 0 || d < 0)
        return false;

    Edge *cur = this->Vertices[s];

    while (cur != nullptr)
    {
        if (cur->Dest == d)
            return true;

        cur = cur->Next;
    }

    return false;
}


//
// AddVertex:
// Adds the given vertex v to the graph, returning true if
// successful and false if not. The add fails if (1) the
// graph is full, or (2) the vertex already exists in the
// graph.
//
bool Graph::AddVertex(string v)
{
    // if the graph is "full", i.e. cannot hold more vertices,
    // then return false:

    if (this->NumVertices >= this->Capacity)
        return false;

    // if the vertex name already exists in the graph,
    // then return false.  To determine, perform a linear
    // search of the Names array
    if (this->FindVertexByName(v) != -1)
        return false;

    //
    // there's room to add another vertex, so grab next index
    // and initialize that linked-list to empty, and store
    // vertex's name:
    //
    int i = this->NumVertices;

    this->Vertices[i] = nullptr;  // head of LL: null
    this->Names[i] = v;           // copy vertex string:

    this->NumVertices++;
    return true;
}


//
// AddEdge:
// Adds an edge from src to dest, with the given weight, returning
// true if successful and false if not. The add fails if the src
// or dest vertex do not exist.
//
bool Graph::AddEdge(string src, string dest, int weight)
{
    // Lookup the vertices for both source and destination names
    int s = this->FindVertexByName(src);
    int d = this->FindVertexByName(dest);
    if (s < 0 || d < 0)
        return false;

    // Add an edge (S,D,weight) to the linked-list in sorted order.
    Edge *e = new Edge();
    e->Src = s;
    e->Dest = d;
    e->Weight = weight;
    e->Next = nullptr;

    if (this->Vertices[s] == nullptr)
        this->Vertices[s] = e;
    else
    {
        Edge *prev = nullptr;
        Edge *cur = this->Vertices[s];

        while (cur != nullptr)
        {
            if (e->Dest < cur->Dest)
                break;
            else if (e->Dest == cur->Dest)
            {
                if (e->Weight <= cur->Weight)
                    break;
            }
            
            prev = cur;
            cur = cur->Next;
        }

        if (prev == nullptr)
        {
            e->Next = cur;
            this->Vertices[s] = e;
        }
        else
        {
            e->Next = cur;
            prev->Next = e;
        }
    }   

    //
    // increment the # of edges and return true:
    //
    this->NumEdges++;
    return true;
}


//
// UpdateEdge:
// Increments the weight of an edge from src to dest.
//
void Graph::UpdateEdge(string src, string dest)
{
    int s = this->FindVertexByName(src);
    int d = this->FindVertexByName(dest);
    if (s < 0 || d < 0)
        return;

    Edge *cur = this->Vertices[s];

    while (cur != nullptr)
    {
        if (cur->Dest == d)
        {
            ++cur->Weight;
            return;
        }

        cur = cur->Next;
    }
}


//
// GetVertices:
// Returns a set containing all vertices in the graph.
//
set<string> Graph::GetVertices()
{
    set<string>  vertices;

    for (int i = 0; i < this->NumVertices; i++)
        vertices.insert(this->Names[i]);

    return vertices;
}


//
// GetWeight:
// Returns the weight for the edge specified
// by src and dest. Returns -1 if either src
// or dest doesn't exist, and returns 0 jf no 
// such edge exists.
//
int Graph::GetWeight(string src, string dest)
{
    int s = this->FindVertexByName(src);
    int d = this->FindVertexByName(dest);
    if (s < 0 || d < 0)
        return -1;

    Edge *cur = this->Vertices[s];

    while (cur != nullptr)
    {
        if (cur->Dest == d)
            return cur->Weight;

        cur = cur->Next;
    }

    return 0;
}


//
// GetNeighbors:
// Returns a set containing all the vertices adjacent to v.
// If v does not exist in the graph, the returned set is
// empty.
//
set<string> Graph::GetNeighbors(string v)
{
    set<string>  neighbors;

    int vertex = FindVertexByName(v);
    if (vertex < 0)
        return neighbors;

    Edge *cur = this->Vertices[vertex];

    while (cur != nullptr)
    {
        neighbors.insert(this->Names[cur->Dest]);
        cur = cur->Next;
    }

    return neighbors;
}


//
// GetEdgeWeights:
// Returns a vector containing all the weights for edges 
// from src to dest.  The weights are in ascending order,
// and may contain duplicates (since it is legal for there
// to be 2 different edges from src to dest with the same
// weight).  If src or dest do not exist in the graph, the
// returned vector is empty.
//
vector<int> Graph::GetEdgeWeights(string src, string dest)
{
    vector<int> weights;

    int s = FindVertexByName(src);
    int d = FindVertexByName(dest);
    if (s < 0 || d < 0)
        return weights;

    Edge *cur = this->Vertices[s];

    while (cur != nullptr)
    {
        if (cur->Dest == d)
            weights.push_back(cur->Weight);

        cur = cur->Next;
    }

    return weights;
}


//
// iNeighbors:
// Returns a vector containing all the vertices adjacent to v.
// If v does not exist in the graph, the returned vector is
// empty. Used by BFS() function
//
vector<int> Graph::iNeighbors(int v)
{
    vector<int>  neighbors;

    Edge *cur = this->Vertices[v];

    while (cur != nullptr)
    {
        neighbors.push_back(cur->Dest);
        cur = cur->Next;
    }

    return neighbors;
}


//
// BFS:
// Performs a breadth-first search starting from vertex v, returning
// a vector that denotes the order in vertices were visited.  If v
// does not exist in the graph, an empty vector is returned.
//
vector<string> Graph::BFS(string v)
{
    vector<string>  visited;
    queue<int>      frontierQueue;
    set<int>        discoveredSet;

    int start = FindVertexByName(v);
    if (start < 0)
        return visited;

    frontierQueue.push(start);
    discoveredSet.insert(start);

    while (!frontierQueue.empty())
    {
        int curVertex = frontierQueue.front();
        frontierQueue.pop();

        // "Visit" curVertex
        visited.push_back(this->Names[curVertex]);

        vector<int> V = iNeighbors(curVertex);
        for (int i : V)
        {
            if (discoveredSet.find(i) == discoveredSet.end())
            {
                frontierQueue.push(i);
                discoveredSet.insert(i);
            }
        }
    }

    return visited;
}