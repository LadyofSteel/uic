//
// Chicago Crime Lookup via hashing
//
// Ammar Subei
// Ubuntu, GCC using Makefile
// U. of Illinois, Chicago
// CS251, Spring2017
// Project #05
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "ht.h"


// Frees hash table and its elements
void HTFree(HT *hashTable, long tableSize)
{
    for(int i = 0; i < tableSize; i++)
    {
        if (hashTable->Bucket[i].Key)
        {
            free(hashTable->Bucket[i].Value->Key);
            free(hashTable->Bucket[i].Value->IUCR);
            free(hashTable->Bucket[i].Value->Date);
            free(hashTable->Bucket[i].Value->AreaName);
            free(hashTable->Bucket[i].Value);
            free(hashTable->Bucket[i].Key);
        }
    }
    free(hashTable->Bucket);
    free(hashTable);
}

// String hashing function
long hash(HTKey key, long N)
{
    long value = 0;

    for(int i = 1; i < strlen(key); i++)
        value = (value * 31) + (int)key[i];

    value = (value << 3);
    value = abs(value);

    return value % N;
}

// Searches key in given array of buckets (basically hashtable)
HTValue *HTSearch(HTBucket *bucket, HTKey key, long tableSize)
{
    int index = hash(key, tableSize);

    if (bucket[index].Key != NULL)
    {
        // If keys match, search successful
        if (!strcmp(bucket[index].Key, key))
            return bucket[index].Value;
        else
        {
            // Linear probing
            int i = index+1;
            while (bucket[i].Key != NULL)
            {
                // If keys match, search successful
                if (!strcmp(bucket[i].Key, key))
                    return bucket[i].Value;

                i++;
                if (i == tableSize)
                    i = 0;
            }

            // Search fails
            return NULL;
        }
    }
    else
        // Search fails
        return NULL;
}

// Inserts key into given HT
int HTInsert(HT *hashTable, HTKey key, HTValue *value, long tableSize)
{
    int index = hash(key, tableSize);

    if (hashTable->Bucket[index].Key != NULL)
    {
        // If keys match, insertion fails
        if (!strcmp(hashTable->Bucket[index].Key, key))
            return 0;
        else
        {
            // Linear probing
            int i = index+1;
            while (hashTable->Bucket[i].Key != NULL)
            {
                // If keys match, insertion fails
                if (!strcmp(hashTable->Bucket[i].Key, key))
                    return 0;

                i++;
                if (i == tableSize)
                    i = 0;

                hashTable->Collisions++;
            }

            hashTable->Bucket[i].Key = (HTKey) malloc(KEYSIZE);
            strcpy(hashTable->Bucket[i].Key, key);
            hashTable->Bucket[i].Value = value;
            hashTable->Count++;

            // Insertion successful
            return 1;
        }
    }
    else
    {
        hashTable->Bucket[index].Key = (HTKey) malloc(KEYSIZE);
        strcpy(hashTable->Bucket[index].Key, key);
        hashTable->Bucket[index].Value = value;
        hashTable->Count++;

        // Insertion successful
        return 1;
    }
}