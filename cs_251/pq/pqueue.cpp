/*pqueue.cpp*/

#include <iostream>
#include <string>

#include "pqueue.h"

using namespace std;


//
// Constructor:
//
PQueue::PQueue()
{
    //
    // TODO: based on implementation strategy
    //
}


// 
// Destructor:
//
PQueue::~PQueue()
{
    // optional, based on implementation strategy:
}


//
// Push:
//
// Inserts the given pair (vertex, distance) into the priority
// queue in ascending order by distance. If two elements of the
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
    // TODO:  
    //
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
    //
    // TODO:
    //

    throw logic_error("stack empty!");
}


//
// Empty:
//
// Returns true if the queue is empty, false if not.
//
bool PQueue::Empty()
{
    //
    // TODO:
    //

    return true;
}


//
// Dump:
//
// Dumps the contents of the queue to the console; this is for
// debugging purposes.
//
void PQueue::Dump(string title)
{
    cout << ">>PQueue: " << title << endl;

    //
    // TODO: compute # of elements in queue:
    //
    int numElements = -1;

    cout << "  # elements: " << numElements << endl;

    if (!this->Empty())
    {
        cout << "  ";

        //
        // TODO: output the elements in priority queue order.  Output
        // each pair (v,d) followed by a space:
        //

        cout << endl;
    }
}