/*pqueue.cpp*/

//
// Priority Queue for Dijkstra's algorithm:
//
// Author: Matt Burkett
// U. of Illinois, Chicago
// CS 251: Spring 2017
//

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "pqueue.h"

using namespace std;


//
// Constructor:
//
PQueue::PQueue()
{
  // internal vector automatically created:
}

//
// Destructor:
//
PQueue::~PQueue()
{
  // internal vector automatically destructed:
}


// Push:
//
// Inserts the given pair (vertex, distance) into the priority
// queue in ascending order by distance.  If two elements of the
// queue have the same distance D, the pairs are ordered by their
// vertex (also in ascending order).
//
// NOTE: if the vertex is already in the queue with distance D',
// then the distance is updated to the new distance D and the
// pair moved to its new position in the queue.
//
void PQueue::Push(int vertex, int distance)
{   
  //
    //finds duplicate, if one exists and deletes it
  //
    auto duplicate = std::find_if(this->vec.begin(), this->vec.end(),
        [=](elem i){
            return (i.vertex == vertex);
        });
    
    if(duplicate != this->vec.end())
        this->vec.erase(duplicate);

  //
    //insert in descending order
  //
    auto insertionPoint = std::find_if(this->vec.begin(), this->vec.end(),
        [=](elem i){
            if(i.distance < distance)
                return true;
            else if (i.distance == distance && i.vertex < vertex)
                return true;
            else
                return false;
        });

    this->vec.insert(insertionPoint, elem(vertex, distance));

    return;
}


//
// PopMin:
//
// Pops (and removes) the (vertex, distance) pair at the front of
// the queue, and returns vertex.  If the queue is empty, then this
// operation is an error and so a logic_error exception is thrown
// with the error message "stack empty!".
//
int PQueue::PopMin()
{
    if (this->Empty())
        throw(std::logic_error("stack empty!"));

    int vertex = this->vec.back().vertex;
    this->vec.pop_back();

    return vertex;
}


//
// Empty:
//
// Returns true if the queue is empty, false if not.
//
bool PQueue::Empty()
{
    return this->vec.empty();
}


//
// Dump:
//
// Dumps the contents of the queue to the console; this is for
// debugging purposes.
//
void PQueue::Dump(std::string title)
{
    std::cout << ">>PQueue: " << title << std::endl;
    int numElements = this->vec.size();

    std::cout << "  # elements: " << numElements << std::endl;

  if (!this->Empty())
  {
    std::cout << "  ";

    for (auto e = this->vec.end() - 1; e >= this->vec.begin(); e--)
    {
      std::cout << "(" << e->vertex << "," << e->distance << ") ";
    }

    std::cout << std::endl;
  }
}
