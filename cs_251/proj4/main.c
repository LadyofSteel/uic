/*main.cpp*/

//
// Divvy Bike Ride Route Analysis, using AVL trees.
//
// Ammar Subei
// U. of Illinois, Chicago
// CS251, Spring 2017
// Project #04
//

// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "avl.h"

#define STATIONTREE 1
#define BIKETREE 0


//
// distBetween2Points: 
//
// Returns the distance in miles between 2 points (lat1, long1) and (lat2, long2).
// 
double distBetween2Points(double lat1, double long1, double lat2, double long2)
{
  //
  // Reference: http://www8.nau.edu/cvm/latlon_formula.html
  //
  double PI = 3.14159265;
  double earth_rad = 3963.1;  // statue miles:

  double lat1_rad = lat1 * PI / 180.0;
  double long1_rad = long1 * PI / 180.0;
  double lat2_rad = lat2 * PI / 180.0;
  double long2_rad = long2 * PI / 180.0;

  double dist = earth_rad * acos(
    (cos(lat1_rad)*cos(long1_rad)*cos(lat2_rad)*cos(long2_rad))
    +
    (cos(lat1_rad)*sin(long1_rad)*cos(lat2_rad)*sin(long2_rad))
    +
    (sin(lat1_rad)*sin(lat2_rad))
  );

  return dist;
}

//
// freeAVLNodeData
//
// Works with AVLFree() to free the data inside (key, value) pairs.
//
void freeAVLNodeData(AVLKey key, AVLValue value)
{
  //
  // what we free depends on what type of value we have:
  //
  if (value.Type == STATIONTYPE)
  {
    free(value.Station.Name);
  }
  else if (value.Type == TRIPTYPE)
  {
  }
  else if (value.Type == BIKETYPE)
  {
  }
  else
  {
    printf("**ERROR: unexpected value type in freeAVLNodeData!\n\n");
    exit(-1);
  }
}

//
// getFileName: 
//
// Inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be 
// opened, an error message is output and the program is exited.
//
char *getFileName()
{
  char filename[512];
  int  fnsize = sizeof(filename) / sizeof(filename[0]);

  // input filename from the keyboard:
  fgets(filename, fnsize, stdin);
  filename[strcspn(filename, "\r\n")] = '\0';  // strip EOL char(s):

  // make sure filename exists and can be opened:
  FILE *infile = fopen(filename, "r");
  if (infile == NULL)
  {
    printf("**Error: unable to open '%s'\n\n", filename);
    exit(-1);
  }

  fclose(infile);

  // duplicate and return filename:
  char *s = (char *)malloc((strlen(filename) + 1) * sizeof(char));
  strcpy(s, filename);

  return s;
}

//
// skipRestOfInput:
//
// Inputs and discards the remainder of the current line for the 
// given input stream, including the EOL character(s).
//
void skipRestOfInput(FILE *stream)
{
  char restOfLine[256];
  int rolLength = sizeof(restOfLine) / sizeof(restOfLine[0]);

  fgets(restOfLine, rolLength, stream);
}

//
// parseLineStations
// Parses a line from stations file, and stores the data accordingly
//
void parseLineStations(char *line, AVLValue *stationValue)
{
  // printf("Parsing line: %s", line);

  line[strcspn(line, "\r\n")] = '\0';

  stationValue->Type = STATIONTYPE;

  stationValue->Station.StationID = atoi(strtok(line, ","));

  char *temp = strtok(NULL, ",");
  stationValue->Station.Name = (char *) malloc(sizeof(char) * 256);
  strcpy(stationValue->Station.Name, temp);

  stationValue->Station.Latitude = atof(strtok(NULL, ","));
  stationValue->Station.Longitude = atof(strtok(NULL, ","));
  stationValue->Station.Capacity = atoi(strtok(NULL, ","));
  stationValue->Station.TripCount = 0;

  temp = strtok(NULL, ",");
}

//
// parseLineTrips:
// Parses a line from trips file, and stores the data accordingly
//
void parseLineTrips(char *line, AVLValue *tripValue, AVLValue *bikeValue)
{
  // printf("Parsing line: %s", line);

  line[strcspn(line, "\r\n")] = '\0';

  tripValue->Type = TRIPTYPE;
  bikeValue->Type = BIKETYPE;

  tripValue->Trip.TripID = atoi(strtok(line, ","));

  char *temp = strtok(NULL, ",");
  temp = strtok(NULL, ",");

  tripValue->Trip.BikeID = atoi(strtok(NULL, ","));

  tripValue->Trip.TripDuration = atoi(strtok(NULL, ","));
  tripValue->Trip.FromID = atoi(strtok(NULL, ","));

  temp = strtok(NULL, ",");

  tripValue->Trip.ToID = atoi(strtok(NULL, ","));

  temp = strtok(NULL, ",");
  temp = strtok(NULL, ",");
  temp = strtok(NULL, ",");
  temp = strtok(NULL, ",");

  bikeValue->Bike.BikeID = tripValue->Trip.BikeID;
  bikeValue->Bike.TripCount = 0;
}

//
// BuildStationsTree:
// Inputs data from stations file and stores in the given AVL tree
//
void buildStationsTree(char* filename, AVL *stationsTree)
{
  FILE *infile = fopen(filename, "r");

  char *line;
  size_t lineSize = 0;

  getline(&line, &lineSize, infile); // Skip first line
  
  while (getline(&line, &lineSize, infile) != -1)
  {
    AVLValue *stationValue = (AVLValue *) malloc(sizeof(AVLValue));
    parseLineStations(line, stationValue);

    AVLInsert(stationsTree, stationValue->Station.StationID, *stationValue);

    free(stationValue);
  }

  free(line);
  fclose(infile);
}

//
// BuildTripsAndBikes:
// Inputs data from trips file and stores in the two given trips and bikes trees
//
void buildTripsAndBikes(char* filename, AVL *tripsTree, AVL *bikesTree)
{
  FILE *infile = fopen(filename, "r");

  char *line;
  size_t lineSize = 0;

  getline(&line, &lineSize, infile);
  
  while (getline(&line, &lineSize, infile) != -1)
  {
    AVLValue *tripValue = (AVLValue *) malloc(sizeof(AVLValue));
    AVLValue *bikeValue = (AVLValue *) malloc(sizeof(AVLValue));
    parseLineTrips(line, tripValue, bikeValue);

    AVLInsert(tripsTree, tripValue->Station.StationID, *tripValue);
    AVLInsert(bikesTree, bikeValue->Station.StationID, *bikeValue);

    free(tripValue);
    free(bikeValue);
  }

  free(line);
  fclose(infile);
}

//
// _updateTripCount:
// Increments the TripCount for the station or bike with given key
//
void _updateTripCount(AVL *tree, AVLKey key, int treeType)
{
  AVLNode *node = AVLSearch(tree, key);

  if (node)
  {
    if (treeType == STATIONTREE)
      node->Value.Station.TripCount++;
    else
      node->Value.Bike.TripCount++;
  }
  else
    return;
}

//
// updateTripCount:
// Updates the TripCount of each node in given tree 
//
void updateTripCount(AVL *tree, AVLNode *root, int treeType)
{
  if (root == NULL)
    return;
  else
  {
    if (treeType == STATIONTREE)
    {
      _updateTripCount(tree, root->Value.Trip.FromID, treeType);
      _updateTripCount(tree, root->Value.Trip.ToID, treeType);
    }
    else
      _updateTripCount(tree, root->Value.Trip.BikeID, treeType);

    updateTripCount(tree, root->Left, treeType);
    updateTripCount(tree, root->Right, treeType);
  }
}

// Sort the movies array by specified criteria using merge sort
// NOTE: almost all the code for MergeSort was taken from zyante
// This function IS NOT of my own writing 
void Merge(AVLNode **stations, int i, int j, int k, double latitude, double longitude) 
{
   int mergedSize = k - i + 1;       // Size of merged partition
   AVLNode *tempStations[mergedSize];     // Temporary array for merged numbers
   int mergePos = 0;                 // Position to insert merged number
   int leftPos = 0;                  // Position of elements in left partition
   int rightPos = 0;                 // Position of elements in right partition
   
   leftPos = i;                      // Initialize left partition position
   rightPos = j + 1;                 // Initialize right partition position
   
  // Add smallest element from left or right partition to merged numbers
  while (leftPos <= j && rightPos <= k) 
  {
    double dist1 = distBetween2Points(latitude, longitude,
      stations[leftPos]->Value.Station.Latitude,
      stations[leftPos]->Value.Station.Longitude);
    double dist2 = distBetween2Points(latitude, longitude,
      stations[rightPos]->Value.Station.Latitude,
      stations[rightPos]->Value.Station.Longitude);

    if (dist1 < dist2) 
    {
      tempStations[mergePos] = stations[leftPos];
      ++leftPos;
    }
    else if (dist1 == dist2)
    {
      if (stations[leftPos]->Key < stations[rightPos]->Key)
      {
        tempStations[mergePos] = stations[leftPos];
        ++leftPos;
      }
      else
      {
        tempStations[mergePos] = stations[rightPos];
        ++rightPos;
      }
    }
    else 
    {
      tempStations[mergePos] = stations[rightPos];
      ++rightPos;
    }
    ++mergePos;
  }

  // If left partition is not empty, add remaining elements to merged numbers
  while (leftPos <= j) 
  {
    tempStations[mergePos] = stations[leftPos];
    ++leftPos;
    ++mergePos;
  }

  // If right partition is not empty, add remaining elements to merged numbers
  while (rightPos <= k) 
  {
    tempStations[mergePos] = stations[rightPos];
    ++rightPos;
    ++mergePos;
  }

  // Copy merge number back to numbers
  for (mergePos = 0; mergePos < mergedSize; ++mergePos)
    stations[i + mergePos] = tempStations[mergePos];
}

// Sort the movies array by specified criteria using merge sort
// NOTE: almost all the code for MergeSort was taken from zyante
// This function IS NOT of my own writing
void MergeSort(AVLNode **stations, int i, int k, double latitude, double longitude) 
{
  int j = 0;

  if (i < k) 
  {
    j = (i + k) / 2;  // Find the midpoint in the partition

    // Recursively sort left and right partitions
    MergeSort(stations, i, j, latitude, longitude);
    MergeSort(stations, j + 1, k, latitude, longitude);

    // Merge left and right partition in sorted order
    Merge(stations, i, j, k, latitude, longitude);
  }
}


void _findStations(AVLNode *root, double latitude, double longitude, double distance, AVLNode **stations, int *i)
{
  if (root == NULL)
    return;
  else
  {
    double distDifference = distBetween2Points(latitude, longitude, root->Value.Station.Latitude, root->Value.Station.Longitude);

    if (distDifference <= distance)
    {
      stations[*i] = root;
      (*i)++;
    }
    
    _findStations(root->Left, latitude, longitude, distance, stations, i);
    _findStations(root->Right, latitude, longitude, distance, stations, i);
  }
}

//
// findStations:
// Finds all the stations in given tree that is a given 
// distance away from the given location (latitude,longitude).
// Returns an array of station nodes
//
AVLNode **findStations(AVL *tree, double latitude, double longitude, double distance)
{
  AVLNode **stations = (AVLNode **) malloc(sizeof(AVLNode) * tree->Count);

  int i = 0;
  while(i < tree->Count)
    stations[i++] = NULL;

  i = 0;
  // Call recursive function that checks the distance for each node
  // and adds that node to the array
  _findStations(tree->Root, latitude, longitude, distance, stations, &i);

  int stationCount = 0;
  i = 0;
  while (stations[i] != NULL)
  {
    i++;
    stationCount++;
  }

  MergeSort(stations, 0, stationCount-1, latitude, longitude);

  return stations;
}


int calcRouteTripCount(AVLNode *root, AVLNode **fromStations, AVLNode **toStations)
{
  if (root == NULL)
    return 0;
  else
  {
    int totalCount = 0;

    int fromID = root->Value.Trip.FromID;
    int toID = root->Value.Trip.ToID;

    for (int i = 0; fromStations[i] != NULL; i++)
    {
      if (fromStations[i]->Key == fromID)
      {
        for (int j = 0; toStations[j] != NULL; j++)
        {
          if (toStations[j]->Key == toID)
            totalCount++;
        }
      }
    }

    totalCount += calcRouteTripCount(root->Left, fromStations, toStations);
    totalCount += calcRouteTripCount(root->Right, fromStations, toStations);

    return totalCount;
  }
}


//
// main:
//
int main()
{
  printf("** Welcome to Divvy Route Analysis **\n");

  //
  // get filenames from the user/stdin:
  //
  char  cmd[64];
  char *StationsFileName = getFileName();
  char *TripsFileName = getFileName();


  AVL *stationsTree = AVLCreate();
  AVL *tripsTree = AVLCreate();
  AVL *bikesTree = AVLCreate();

  buildStationsTree(StationsFileName, stationsTree);
  buildTripsAndBikes(TripsFileName, tripsTree, bikesTree);

  // Update the TripCount for all stations and bikes
  updateTripCount(stationsTree, tripsTree->Root, STATIONTREE);
  updateTripCount(bikesTree, tripsTree->Root, BIKETREE);

  //
  // now interact with user:
  //
  printf("** Ready **\n");

  scanf("%s", cmd);

  while (strcmp(cmd, "exit") != 0)
  {
    if (strcmp(cmd, "stats") == 0)
    {
      //
      // Output some stats about our data structures:
      //
      printf("** Trees:\n");

      printf("   Stations: count = %d, height = %d\n",
        AVLCount(stationsTree), AVLHeight(stationsTree));

      printf("   Trips:    count = %d, height = %d\n",
        AVLCount(tripsTree), AVLHeight(tripsTree));

      printf("   Bikes:    count = %d, height = %d\n",
        AVLCount(bikesTree), AVLHeight(bikesTree));
    }
    else if (strcmp(cmd, "station") == 0)
    {
      int id = 0;
      scanf("%d", &id);

      AVLNode *result = AVLSearch(stationsTree, id);
      if (result)
      {
        printf("**Station %d:\n", result->Key);
        printf("  Name: '%s'\n", result->Value.Station.Name);
        printf("  Location:   (%f,%f)\n", result->Value.Station.Latitude, result->Value.Station.Longitude);
        printf("  Capacity:   %d\n", result->Value.Station.Capacity);
        printf("  Trip count: %d\n", result->Value.Station.TripCount);
      }

      else
        printf("**not found\n");
    }
    else if (strcmp(cmd, "trip") == 0)
    {
      int id = 0;
      scanf("%d", &id);

      AVLNode *result = AVLSearch(tripsTree, id);
      if (result)
      {
        // Need to compute the duration in (minutes,seconds) form
        int seconds;
        int minutes;

        seconds = result->Value.Trip.TripDuration % 60;
        minutes = result->Value.Trip.TripDuration / 60;

        printf("**Trip %d:\n", result->Key);
        printf("  Bike: %d\n", result->Value.Trip.BikeID);
        printf("  From: %d\n", result->Value.Trip.FromID);
        printf("  To:   %d\n", result->Value.Trip.ToID);
        printf("  Duration: %d min, %d secs\n", minutes, seconds);
      }

      else
        printf("**not found\n");
    }
    else if (strcmp(cmd, "bike") == 0)
    {
      int id = 0;
      scanf("%d", &id);

      AVLNode *result = AVLSearch(bikesTree, id);
      if (result)
      {
        printf("**Bike %d:\n", result->Key);
        printf("  Trip count: %d\n",result->Value.Bike.TripCount);
      }

      else
        printf("**not found\n");
    }
    else if (strcmp(cmd, "find") == 0)
    {
      double latitude;
      double longitude;
      double distance;

      scanf("%lf %lf %lf", &latitude, &longitude, &distance);

      AVLNode **stations = findStations(stationsTree, latitude, longitude, distance);

      for (int i = 0; stations[i] != NULL; i++)
        printf("Station %d: distance %lf miles\n", stations[i]->Key, 
          distBetween2Points(stations[i]->Value.Station.Latitude,
            stations[i]->Value.Station.Longitude,latitude, longitude));

      free (stations);
    }
    else if (strcmp(cmd, "route") == 0)
    {
      int tripID;
      int tripCount;
      double distance;

      scanf("%d %lf", &tripID, &distance);

      // Find route:
        // For given tripID, get fromID and toID
      AVLNode *node = AVLSearch(tripsTree, tripID);
      if (node)
      {
        int fromID = node->Value.Trip.FromID;
        int toID = node->Value.Trip.ToID;

        printf("** Route: from station #%d to station #%d\n", fromID, toID);


        AVLNode *S = AVLSearch(stationsTree, fromID);
        AVLNode *D = AVLSearch(stationsTree, toID);

        AVLNode **SPrime = findStations(stationsTree, S->Value.Station.Latitude, 
                                        S->Value.Station.Longitude, distance);
        AVLNode **DPrime = findStations(stationsTree, D->Value.Station.Latitude,
                                    D->Value.Station.Longitude, distance);


        tripCount = calcRouteTripCount(tripsTree->Root, SPrime, DPrime);

        printf("** Trip count: %d\n", tripCount);

        double percentage = ((double)tripCount / (double)(tripsTree->Count)) * 100.0;

        printf("** Percentage: %lf%%\n", percentage);

        free(SPrime);
        free(DPrime);
      }
      else
        printf("**not found\n");
    }
    else
    {
      printf("**unknown cmd, try again...\n");
    }

    scanf("%s", cmd);
  }

  // printf("%lf\n", distBetween2Points(41.94302616, -87.68739454, 41.943020, -87.687399));

  //
  // done, free memory and return:
  //
  printf("** Freeing memory **\n");

  free(StationsFileName);
  free(TripsFileName);

  AVLFree(stationsTree, freeAVLNodeData);
  AVLFree(tripsTree, freeAVLNodeData);
  AVLFree(bikesTree, freeAVLNodeData);

  printf("** Done **\n");

  return 0;
}