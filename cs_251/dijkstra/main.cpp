/*main.cpp*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "graph.h"

using namespace std;

#define _CRT_SECURE_NO_WARNINGS  // ignore C-related security warnings in Visual Studio:


Graph BuildGraph(istream& input)
{
  int    N;
  string line;
  
  input >> N;  // graph size:
  getline(input, line);  // discard rest of that line

  Graph G(N);  // create graph

  //
  // input vertices and edges, one per line:
  //
  getline(input, line);
  while (line != "#")  // for each line of input:
  {
    stringstream  ss(line);

    string cmd, vertex, src, dest, weightStr;

    getline(ss, cmd, ',');

    if (cmd == "v")  // add vertex:
    {
      getline(ss, vertex);

      bool success = G.AddVertex(vertex);
      if (!success)
        cout << "**AddVertex failed: " << line << endl;
      else
        cout << "  Added vertex: " << vertex << endl;
    }
    else if (cmd == "e")  // add edge:
    {
      // parse line: src,dest,weight:
      string  src, dest, weightStr;

      getline(ss, src, ',');
      getline(ss, dest, ',');
      getline(ss, weightStr);

      int weight = stoi(weightStr);

      bool success = G.AddEdge(src, dest, weight);
      if (!success)
        cout << "**AddEdge failed: (" << src << "," << dest << "," << weightStr << ")" << endl;
      else
        cout << "  Added edge: " << src << "," << dest << "," << weightStr << endl;
    }
    else
    {
      cout << "**Error: unknown input cmd ('" << cmd << "')" << endl;
    }

    getline(input, line);
  }

  //
  // done:
  //
  return G;
}


//#define VS


int main()
{
  cout << "**Building Graph**" << endl;

#ifdef VS
  ifstream  input("values-1.txt");
  Graph G = BuildGraph(input);
#else
  istream& input = cin;
  Graph G = BuildGraph(input);
#endif

  cout << "**Printing Graph**" << endl;

  G.PrintGraph("Cities");

  //
  // input the src and dest for Dijkstra's alg:
  //
  string src, dest;
  int weight;
  vector<string> path;
  vector<string> visited;

  input >> src;
  input >> dest;

  //
  // call Dijkstra and see what we get back:
  //
  cout << "**Dijkstra(" << src << "," << dest << ")**" << endl;

  bool success = G.Dijkstra(src, dest, weight, path, visited);

  if (!success)
  {
    cout << ">>no path..." << endl;
  }
  else
  {
    cout << ">> Weight: " << weight << endl;

    cout << ">> Path:   ";

    for (string v : path)  // output each vertex in the path:
    {
      cout << v;

      if (v != dest)
        cout << "->";
    }

    cout << endl;

    cout << ">> Visited: ";

    for (int i = 0; i < visited.size(); ++i)
    {
      cout << visited[i];

      if (i < visited.size() - 1)
        cout << ",";
    }

    cout << endl;
  }

  //
  // done:
  //
  cout << "**Done**" << endl;
  return 0;
}
