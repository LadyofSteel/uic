/*pqueue.h*/

#pragma once

#include <string>
#include <exception>
#include <stdexcept>

using namespace std;


class PQueue
{
    private:
        
    public:
        PQueue();   // constructor:
        ~PQueue();  // destructor:

        void Push(int vertex, int distance);
        int  PopMin();
        bool Empty();

        void Dump(string title);  // debugging output of contents:
};
