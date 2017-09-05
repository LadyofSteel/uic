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


long getFileSizeInBytes(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return -1;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    return size;
}

char *getFileName()
{
    char filename[512];
    int  fnsize = sizeof(filename) / sizeof(filename[0]);

    // Input filename from the keyboard:
    fgets(filename, fnsize, stdin);
    filename[strcspn(filename, "\r\n")] = '\0';

    // Make sure filename exists and can be opened:
    FILE *infile = fopen(filename, "r");
    if (infile == NULL)
    {
        printf("**Error: unable to open '%s'\n\n", filename);
        exit(-1);
    }

    fclose(infile);

    // Duplicate and return filename:
    char *s = (char *)malloc((strlen(filename) + 1) * sizeof(char));
    strcpy(s, filename);

    return s;
}

//
// buildHashTable:
// Returns an initialized hashtable
// 
HT *buildHashTable(long tableSize)
{
    HT *hashTable = (HT *) malloc(sizeof(HT));
    hashTable->Bucket = (HTBucket *) malloc( sizeof(HTBucket) * tableSize);
    hashTable->Count = 0;
    hashTable->Collisions = 0;

    for(int i = 0; i < tableSize; i++)
    {
        hashTable->Bucket[i].Key = NULL;
        hashTable->Bucket[i].Value = NULL;
    }

    return hashTable;
}

//
// extractAreaNum:
// Returns area number from given key
//
int extractAreaNum(HTKey key)
{
    int number;
    char temp[3];

    strncpy(temp, key, 3);
    number = atoi(&(temp[1]));

    return number;
}

//
// readFiles:
// Inputs data from crimes and areas files 
// and stores the info in the given HT
//
void readFiles(char* crimesFile, char *areasFile, HT *hashTable, long tableSize)
{
    FILE *inCrimes = fopen(crimesFile, "r");
    FILE *inAreas = fopen(areasFile, "r");

    char *areas[78];

    char crimeLine[64];
    char areaLine[32];

    size_t crimeLineSize = 64;
    size_t areaLineSize = 32;

    // Skip first lines
    fgets(crimeLine, crimeLineSize, inCrimes);
    fgets(areaLine, areaLineSize, inAreas);

    // First store each area line into array
    int index = 0;
    while (fgets(areaLine, areaLineSize, inAreas))
    {
        areaLine[strcspn(areaLine, "\r\n")] = '\0';

        char *temp = strtok(areaLine, ",");
        temp = strtok(NULL, ",");
        areas[index] = (char *) malloc(30);
        strcpy(areas[index], temp);

        index++;
    }

    // Now store the crime info into HT
    while (fgets(crimeLine, crimeLineSize, inCrimes))
    {    
        crimeLine[strcspn(crimeLine, "\r\n")] = '\0';

        HTValue *value = (HTValue *) malloc(sizeof(HTValue));
        value->Key = (HTKey) malloc(8);
        value->IUCR = (char *) malloc(4);
        value->Date = (char *) malloc(10);
        value->Arrested = (char *) malloc(2);
        value->AreaName = (char *) malloc(16);

        char *temp = strtok(crimeLine, ",");
        strcpy(value->Key, temp);

        int areaNum = extractAreaNum(temp);
        value->AreaNumber = areaNum;
        strcpy(value->AreaName, areas[areaNum]);

        temp = strtok(NULL, ",");
        strcpy(value->IUCR, temp);

        temp = strtok(NULL, ",");
        strcpy(value->Date, temp);

        temp = strtok(NULL, ",");
        temp = strtok(NULL, ",");
        temp = strtok(NULL, ",");

        temp = strtok(NULL, ",");
        strcpy(value->Arrested, temp);

        HTInsert(hashTable, value->Key, value, tableSize);
    }

    // Gotta free areas array
    free(*areas);

    fclose(inCrimes);
    fclose(inAreas);
}

//
// isKeyValid:
// Checks the given key if it's valid
//
int isKeyValid(HTKey key)
{   
    if (strlen(key) < 8 || strlen(key) > 8)
        return 0;

    int num1, num2;
    if (sscanf(key, "R%2d%*[A-Z]%4d", &num1, &num2))
    {
        if (num1 > 0 && num1 < 78)
            return 1;
    }

    return 0;
}


int main()
{
    // Get file names
    char *CrimesFile = getFileName();
    char *AreasFile = getFileName();

    // Calculate the size of crimes file and size of HT
    long crimeFileSize = getFileSizeInBytes(CrimesFile);
    long N = (crimeFileSize / 10);

    // Initialize HT
    HT *hashTable = buildHashTable(N);

    // Input data from files into HT
    readFiles(CrimesFile, AreasFile, hashTable, N);

    // Print HT stats
    printf(">> Crimes file: %ld bytes\n", crimeFileSize);
    printf(">> # crimes:    %ld\n", hashTable->Count);
    printf(">> HT size:     %ld\n", N);
    printf(">> Collisions:  %d\n", hashTable->Collisions);

    // User input loop
    while(1)
    {
        char inputKey[16];

        printf("\nEnter a case number> ");

        // User input
        fgets(inputKey, 16, stdin);
        inputKey[strcspn(inputKey, "\r\n")] = '\0';

        // End program if nothing was entered
        if (!(*inputKey))
            break;

        // Search for case number if it's valid
        if (isKeyValid(inputKey))
        {
            HTValue *value = HTSearch(hashTable->Bucket, inputKey, N);
            if (value)
            {   
                printf(">> hash index: %ld <<\n", hash(inputKey, N));
                printf("%s:\n", inputKey);
                printf("  date/time: %s\n", value->Date);
                printf("  city area: %d => %s\n", value->AreaNumber, value->AreaName);
                printf("  IUCR code: %s\n", value->IUCR);

                char *arrested;
                if (!strcmp(value->Arrested, "T"))
                    arrested = "true";
                else
                    arrested = "false";

                printf("  arrested:  %s\n", arrested);
            }
            else
                printf("** Case not found...\n");
        }
        else
            printf("** invalid case #, try again...\n");
    }

    // End of program
    free(CrimesFile);
    free(AreasFile);
    HTFree(hashTable, N);
    
    printf("** Done **\n");
}