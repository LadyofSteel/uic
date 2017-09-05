/*pqueue.h*/

//
// Priority Queue for Dijkstra's algorithm:
//
// Author: Matt Burkett
// U. of Illinois, Chicago
// CS 251: Spring 2017
//

#pragma once

#include <string>
#include <exception>
#include <stdexcept>
#include <vector>

using namespace std;


class PQueue
{
private:
    class elem
    {
    public:
        int vertex;
        int distance;

    elem(int vertex, int distance)
    {
      this->vertex = vertex;
      this->distance = distance;
    }
    };

    vector<elem> vec;

public:
  PQueue();
  ~PQueue();
  
  void Push(int vertex, int distance);
    int  PopMin();
    bool Empty();
    void Dump(string title);
};
