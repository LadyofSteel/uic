/*main.cpp*/

#include <iostream>
#include <fstream>
#include <string>

#include "pqueue.h"

using namespace std;

#define _CRT_SECURE_NO_WARNINGS  // ignore C-related security warnings in Visual Studio:


int main()
{
    cout << "**Starting Test**" << endl;
    
    istream& input = cin;

    PQueue  pq;
    int     vertex, distance;

    string  cmd;
    input >> cmd;

    while (cmd != "exit")
    {
        if (cmd == "push")
        {
            input >> vertex;
            input >> distance;

            pq.Push(vertex, distance);

            cout << "Push: (" << vertex << "," << distance << ")" << endl;
        }

        else if (cmd == "pop")
        {
            cout << "PopMin: ";

            try
            {
                int v = pq.PopMin();
                cout << "vertex " << v;
            }
            catch (logic_error& le)
            {
                cout << le.what();
            }
            catch (...)
            {
                cout << "unknown exception...";
            }

            cout << endl;
        }

        else if (cmd == "empty")
            cout << "Empty: " << pq.Empty() << endl;

        else if (cmd == "dump")
        {
            string step;
            input >> step;
            pq.Dump("Step " + step);
        }
        else
        {
            cout << "**invalid cmd..." << endl;
        }

        input >> cmd;
    }

    cout << "**Done**" << endl;
    return 0;
}
