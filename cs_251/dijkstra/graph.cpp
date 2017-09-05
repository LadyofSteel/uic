/*graph.cpp*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <limits>
#include <exception>
#include <stdexcept>

#include "pqueue.h"
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
// FindVertexByName:
//
// Helper function to find a vertex by name by
// searching the Names array using linear search.
// Returns vertex # (i.e. array index) or -1 if 
// not found:
//
int Graph::FindVertexByName(string name)
{
  for (int i = 0; i < this->NumVertices; ++i)
  {
    if (this->Names[i] == name)
    {
      return i;
    }
  }

  // if get here, not found:
  return -1;
}


//
// AddVertex:
//
// Adds the given vertex v to the graph, returning true if
// successful and false if not.  The add fails if (1) the
// graph is full, or (2) the vertex already exists in the
// graph.
//
bool Graph::AddVertex(string v)
{
  if (FindVertexByName(v) >= 0)  // vertex already exists?
    return false;  // add failed:

  // 
  // is the graph full?
  //
  if (this->NumVertices == this->Capacity)  // is graph "full"?
  {
    int newCap = this->Capacity * 2;

    Edge **newVertices = new Edge*[newCap];
    string *newNames = new string[newCap];

    for (int i = 0; i < this->Capacity; i++)
    {
      newVertices[i] = this->Vertices[i];
      newNames[i] = this->Names[i];
    }

    delete [] this->Vertices;
    delete [] this->Names;

    this->Vertices = newVertices;
    this->Names = newNames;
    this->Capacity = newCap;
  }

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
//
// Adds an edge from src to dest, with the given weight, returning
// true if successful and false if not.  The add fails if the src
// or dest vertex do not exist.
//
bool Graph::AddEdge(string src, string dest, int weight)
{
  int vsrc = FindVertexByName(src);
  int vdest = FindVertexByName(dest);

  if (vsrc == -1 || vdest == -1)
    return false;

  Edge *e = new Edge();
  e->Src = vsrc;
  e->Dest = vdest;
  e->Weight = weight;

  //
  // The list of edges are in sorted order by destination, so we 
  // have to traverse list and find insertion spot:
  //
  Edge *prev = nullptr;
  Edge *cur = this->Vertices[vsrc];
  while (cur != nullptr)
  {
    if (e->Dest < cur->Dest)  // found insertion spot:
      break;
    else if (e->Dest == cur->Dest) // then order by weight:
    {
      if (e->Weight <= cur->Weight)
        break;
    }

    prev = cur;
    cur = cur->Next;
  }

  e->Next = cur;  // cur and remaining nodes follow e:
  if (prev == nullptr)  // no prev to update, so e is head of LL:
    this->Vertices[vsrc] = e;
  else  // else e now follows prev node:
    prev->Next = e;

  this->NumEdges++;
  return true;
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
// iNeighbors:
//
// Returns the neighbors of v --- internal vertex neighbors.
//
vector<int> Graph::iNeighbors(int v)
{
  vector<int>  neighbors;

  Edge *cur = this->Vertices[v];
  while (cur != nullptr)
  {
    int dest = cur->Dest;
    neighbors.push_back(dest);

    cur = cur->Next;
  }

  return neighbors;
}


//
// Dijkstra
//
// Performs Dijkstra's shortest weighted path algorithm, finding the shortest path from
// src to dest.  If such a path exists, then:
//
//    1. weight is set to the total weight along the path
//    2. path is set to the shortest weighted path from src to dest
//    3. visited is set to the vertices in the order they are visited
//    4. true is returned.
//
// If no path exists, then false is returned and the reference parameters
// are undefined.
//
bool Graph::Dijkstra(string src, string dest, int& weight, vector<string>& path, vector<string>& visited)
{
  weight = -1;  // clear parameters in case we return false:
  path.clear();
  visited.clear();

  int vsrc = FindVertexByName(src);
  int vdest = FindVertexByName(dest);

  if (vsrc == -1 || vdest == -1)
    return false;

  //
  // first we need to create internal distances and predecessors arrays:
  //
  int *distances = new int[this->NumVertices];
  int *predecessors = new int[this->NumVertices];
  PQueue unvisitedQueue;

  const int INF = numeric_limits<int>::max();

  for (int i = 0; i < this->NumVertices; ++i)
  {
    distances[i] = INF;
    predecessors[i] = -1;
    
    unvisitedQueue.Push(i, INF);
  }

  //
  // we start @ src:
  //
  distances[vsrc] = 0;
  unvisitedQueue.Push(vsrc, 0);  // update distance in priority queue:

  //
  // Now let's run Dijkstra's algorithm:
  //

  while(!unvisitedQueue.Empty())
  {
    int curV = unvisitedQueue.PopMin();

    // Check if vertex is already visited
    bool found = false;
    for (string name : visited)
    {
      if (name == this->Names[curV])
      {
        found = true;
        break;
      }
    }

    // Add to vector if not visited
    if (!found)
      visited.push_back(this->Names[curV]);

    if (distances[curV] == INF)
      break;

    Edge *vertex = this->Vertices[curV];

    // For every adjacent vertex
    while (vertex != nullptr)
    {
      int adjV = vertex->Dest;
      int edgeWeight = vertex->Weight;
      int altDistance = distances[curV] + edgeWeight;

      if (altDistance < distances[adjV])
      {
        distances[adjV] = altDistance;
        predecessors[adjV] = curV;
        unvisitedQueue.Push(adjV, altDistance);
      }
      
      vertex = vertex->Next;
    }
  }


  //
  // Done, did we reach the destination?
  //
  if (distances[vdest] == INF)  // no...
    return false;

  weight = distances[vdest];

  int v = vdest;
  stack<int> test;

  while (v != -1)
  {
    test.push(v);
    v = predecessors[v];
  }
     
   while (!test.empty())
   {

     path.push_back(this->Names[test.top()]);
     test.pop();
   }

  // done!
  return true;
}