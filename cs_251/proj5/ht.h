//
// Chicago Crime Lookup via hashing
//
// Ammar Subei
// Ubuntu, GCC using Makefile
// U. of Illinois, Chicago
// CS251, Spring2017
// Project #05
//

#pragma once

#define KEYSIZE 8

typedef char *HTKey;

typedef struct HTValue
{
    HTKey Key;
    char *IUCR;
    char *Date;
    char *AreaName;
    char *Arrested;
    int AreaNumber;
} HTValue;

typedef struct HTBucket
{
    HTKey Key;
    HTValue *Value;
} HTBucket;

typedef struct HT
{
    HTBucket *Bucket;
    long Count;
    int Collisions;
} HT;


void HTFree(HT *hashTable, long tableSize);

long hash(HTKey key, long N);
int HTInsert(HT *hashTable, HTKey key, HTValue *value, long tableSize);

HTValue *HTSearch(HTBucket *bucket, HTKey key, long tableSize);