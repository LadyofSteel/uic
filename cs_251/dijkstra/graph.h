/*graph.h*/

#pragma once

#include <string>
#include <vector>
#include <limits>

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
  Graph(int N);
  ~Graph();

  bool AddVertex(string v);
  bool AddEdge(string src, string dest, int weight);

  void PrintGraph(string title);

  bool Dijkstra(string src, string dest, int& weight, vector<string>& path, vector<string>& visited);
};
