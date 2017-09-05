/*avl.h*/

//
// AVL Tree ADT header file.
//
// Ammar Subei
// U. of Illinois, Chicago
// CS251, Spring 2017
//

// make sure this header file is #include exactly once:
#pragma once


//
// AVL type declarations:
//
typedef int  AVLKey;

typedef struct STATION
{
  int     StationID;
  char    *Name;
  double  Latitude;
  double  Longitude;
  int     Capacity;
  int     TripCount;

} STATION;

typedef struct TRIP
{
  int TripID;
  int BikeID;
  int TripDuration;
  int FromID;
  int ToID;

} TRIP;

typedef struct BIKE
{
  int  BikeID;
  int  TripCount;

} BIKE;

enum UNIONTYPE
{
  STATIONTYPE,
  TRIPTYPE,
  BIKETYPE
};

typedef struct AVLValue
{
  enum UNIONTYPE Type;  // Station, Trip, or Bike:
  union
  {
    STATION  Station;   // union => only ONE of these is stored:
    TRIP     Trip;
    BIKE     Bike;
  };
} AVLValue;

typedef struct AVLNode
{
  AVLKey    Key;
  AVLValue  Value;
  struct AVLNode  *Left;
  struct AVLNode  *Right;
  int       Height;
} AVLNode;

typedef struct AVL
{
  AVLNode *Root;
  int      Count;
} AVL;


//
// AVL API: function prototypes
//
AVL *AVLCreate();
void AVLFree(AVL *tree, void(*fp)(AVLKey key, AVLValue value));

int      AVLCompareKeys(AVLKey key1, AVLKey key2);
AVLNode *AVLSearch(AVL *tree, AVLKey key);
int      AVLInsert(AVL *tree, AVLKey key, AVLValue value);

int  AVLCount(AVL *tree);
int  AVLHeight(AVL *tree);
