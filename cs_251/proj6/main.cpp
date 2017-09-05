/*main.cpp*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>

#include "graph.h"

using namespace std;

#define _CRT_SECURE_NO_WARNINGS  // ignore C-related security warnings in Visual Studio:


//
// Defines a Divvy Station:
//
class Station
{
    public:
    string Name;
    int    ID;
    double Latitude;
    double Longitude;
    int    Capacity;

    Station(string name, int id, double latitude, double longitude, int capacity)
    {
        Name = name;
        ID = id;
        Latitude = latitude;
        Longitude = longitude;
        Capacity = capacity;
    }
};


//
// getFileName: 
// Inputs a filename from the keyboard, checks that the file can be
// opened, and returns the filename if so.  If the file cannot be 
// opened, an error message is output and the program is exited.
//
string getFileName()
{
    string filename;

    // input filename from the keyboard:
    getline(cin, filename);

    // make sure filename exists and can be opened:
    ifstream file(filename);
    if (!file.good()) 
    {
        cout << "**Error: unable to open '" << filename << "'" << endl << endl;
        std::terminate();
    }

    return filename;
}


//
// Inputs the stations from the given file, adding each station name as a
// vertex to the graph, and storing a new Station object into the vector.
// The graph is passed by reference --- note the & --- so that the changes
// made by the function are returned back.  The vector of Station objects is
// returned by the function.
//
vector<Station> InputStations(Graph& G, string filename)
{
    string line;
    vector<Station> V;

    ifstream input(filename);
    if (!input.good())  // failed to open:
        return V;

    getline(input, line);  // skip first line: column headers
    getline(input, line);  // first line of real data

    while (!input.eof())  // for each line of input:
    {
        stringstream  ss(line);

        // format:
        //   id,name,latitude,longitude,dpcapacity,online_date
        //   456,2112 W Peterson Ave,41.991178,-87.683593,15,5/12/2015
        //   101,63rd St Beach,41.78101637,-87.57611976,23,4/20/2015
        //
        string  stationID, name, latitude, longitude, capacity;

        //
        // parse the line:
        //
        getline(ss, stationID, ',');
        getline(ss, name, ',');
        getline(ss, latitude, ',');
        getline(ss, longitude, ',');
        getline(ss, capacity, ',');

        //
        // Create a new station object:
        //
        Station S(name, 
        stoi(stationID), 
        stod(latitude), 
        stod(longitude), 
        stoi(capacity));

        V.push_back(S);
        G.AddVertex(name);

        getline(input, line);
    }

    return V;
}


//
// Inputs the trips, adding / updating the edges in the graph.  The graph is
// passed by reference --- note the & --- so that the changes made by the 
// function are returned back.  The vector of stations is needed so that 
// station ids can be mapped to names; it is passed by reference only for 
// efficiency (so that a copy is not made).
//
void ProcessTrips(string filename, Graph& G, vector<Station>& stations)
{
    string line;

    ifstream input(filename);
    if (!input.good())  // failed to open:
        return;

    getline(input, line);  // skip first line: column headers
    getline(input, line);  // first line of real data

    while (!input.eof())  // for each line of input:
    {
        stringstream  ss(line);

        // format:
        //   trip_id,starttime,stoptime,bikeid,tripduration,from_station_id,from_station_name,to_station_id,to_station_name,usertype,gender,birthyear
        //   10426561,6/30/2016 23:35,7/1/2016 0:02,5229,1620,329,Lake Shore Dr & Diversey Pkwy,307,Southport Ave & Clybourn Ave,Subscriber,Male,1968
        //
        string  tripID, fromID, toID, skip;

        //
        // parse the input line:
        //
        getline(ss, tripID, ',');
        getline(ss, skip, ',');
        getline(ss, skip, ',');
        getline(ss, skip, ',');
        getline(ss, skip, ',');
        getline(ss, fromID, ',');
        getline(ss, skip, ',');
        getline(ss, toID, ',');
        getline(ss, skip);

        // Get the "from" and "to" stations from our stations vector
        vector<Station>::iterator fromStation = find_if(stations.begin(), stations.end(),
            [=] (Station s)
            {
                return s.ID == stoi(fromID);
            } );

        vector<Station>::iterator toStation = find_if(stations.begin(), stations.end(),
            [=] (Station s)
            {
                return s.ID == stoi(toID);
            } );

        // We need to use the station names for our graph modifications
        string fromName = fromStation->Name;
        string toName = toStation->Name;

        // Increment edge weight if edge exists
        if (G.EdgeExists(fromName, toName))
            G.UpdateEdge(fromName, toName);
        // Otherwise add it as a new edge
        else
            G.AddEdge(fromName, toName, 1);

        getline(input, line);
    }
}


//
// InfoCommand:
// Handles the case where the user enters the "info id" command.
// Outputs the desired information about the station with the given
// stationID "id"
//
void InfoCommand(Graph& G, vector<Station>& S)
{
    int fromID;
    cin >> fromID;

    // Find station object with matching IDs
    auto station = find_if(S.begin(), S.end(),
    [=] (Station s)
    {
        return s.ID == fromID;
    } );

    // Check if station exists
    if (station == S.end())
        cout << "** No such station..." << endl;
    else
    {
        // Get info from station object
        string stationName = station->Name;
        double stationLat = station->Latitude;
        double stationLong = station->Longitude;
        int stationCap = station->Capacity;

        // Get the neighbors to that station 
        set<string> neighbors = G.GetNeighbors(stationName);

        int tripCount = 0;

        // For every neighbor, sum up all weights  
        for (auto neighbor : neighbors)
        {
            vector<int> weights = G.GetEdgeWeights(stationName, neighbor);

            tripCount += accumulate(weights.begin(), weights.end(), 0);
        }

        // Print station info
        cout << stationName << endl;
        cout << "(" << stationLat << "," << stationLong << ")" << endl;
        cout << "Capacity: " << stationCap << endl;
        cout << "# of destination stations:    " << neighbors.size() << endl;
        cout << "# of trips to those stations: " << tripCount << endl;

        cout << "Station: trips" << endl;

        // For each neighbor, print its info
        for (auto neighbor : neighbors)
        {
            auto station = find_if(S.begin(), S.end(),
            [=] (Station s)
            {
                return s.Name == neighbor;
            } );

            int weight = G.GetWeight(stationName, neighbor);

            cout << "  " << neighbor << " (" << station->ID << "): " << weight << endl;
        }
    }
}


//
// TripsCommand:
// Handles the case where the user enters the "trips toID fromID" command.
// Outputs the desired information about the edge from "fromID" to "toID".
//
void TripsCommand(Graph& G, vector<Station>& S)
{
    int fromID, toID;

    cin >> fromID; 
    cin >> toID;

    // Find fromStation and toStation using fromID and toID
    vector<Station>::iterator fromStation = find_if(S.begin(), S.end(),
    [=] (Station s)
    {
        return s.ID == fromID;
    } );

    vector<Station>::iterator toStation = find_if(S.begin(), S.end(),
        [=] (Station s)
        {
            return s.ID == toID;
        } );

    // Check if the stations exist
    if (fromStation == S.end() || toStation == S.end())
    {
        cout << "** One of those stations doesn't exist..." << endl;
        return;
    }

    // Use station names to get the weight of the edge
    string fromName = fromStation->Name;
    string toName = toStation->Name;

    int weight = G.GetWeight(fromName, toName);
            
    // Print the results
    cout << fromName <<  " -> " << toName << endl;
    cout << "# of trips: " << weight << endl;
}


//
// BFSCommand:
// Handles the case where the user enters the "bfs id" command.
// Outputs the desired information about the stations resulting
// from the breadth-first search.
//
void BFSCommand(Graph& G, vector<Station>& S)
{
    int fromID;
    cin >> fromID;

    // Find station name from given ID
    auto fromStation = find_if(S.begin(), S.end(),
    [=] (Station s)
    {
        return s.ID == fromID;
    } );

    // Check if station exists
    if (fromStation == S.end())
    {
        cout << "** No such station..." << endl;
        return;
    }

    // Use station name to perform BFS on our graph
    string fromName = fromStation->Name;
    vector<string> bfsStations = G.BFS(fromName);

    cout << "# of stations: " << bfsStations.size() << endl;

    // For every station name in our BFS result
    for (auto name : bfsStations)
    {   
        // Get the corresponding station ID and print it out
        auto station = find_if(S.begin(), S.end(),
        [=] (Station s)
        {
            return s.Name == name;
        } );

        cout << station->ID << ", ";
    }

    cout << "#" << endl;
}


int main()
{
    int    N = 1000;
    Graph  DivvyGraph(N);

    cout << "** Divvy Graph Analysis **" << endl;

    string stationsFilename = getFileName();
    string tripsFilename = getFileName();

    vector<Station> stations = InputStations(DivvyGraph, stationsFilename);
    ProcessTrips(tripsFilename, DivvyGraph, stations);

    cout << ">> Graph:" << endl;
    cout << "   # of vertices: " << DivvyGraph.GetNumVertices() << endl;
    cout << "   # of edges:    " << DivvyGraph.GetNumEdges() << endl;
    cout << ">> Ready:" << endl;

    string cmd;

    cout << ">> ";
    cin >> cmd;

    while (cmd != "exit")
    {
        if (cmd == "info")
            InfoCommand(DivvyGraph, stations);
        else if (cmd == "trips")
        {
            TripsCommand(DivvyGraph, stations);
        }
        else if (cmd == "bfs")
        {
            BFSCommand(DivvyGraph, stations);
        }
        else if (cmd == "debug")
        {
            DivvyGraph.PrintGraph("Divvy Graph");
        }
        else
        {
            cout << "**Invalid command, try again..." << endl;
        }

        cout << ">> ";
        cin >> cmd;
    }

    cout << "**Done**" << endl;
    return 0;
}