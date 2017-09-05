/*main.cpp*/

//
// Auto-complete using a binary search tree.
//
// Ammar Subei
// U. of Illinois, Chicago
// CS251, Spring 2017
// Project 03
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "bst.h"


// swap:
// A utility function to swap two elements
void swap(BSTValue *a, BSTValue *b)
{
    BSTValue t = *a;
    *a = *b;
    *b = t;
}


// partition:
/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (BSTValue *values, int low, int high)
{
    BSTValue pivot = values[high];    // pivot

    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current weight is greater than pivot weight
        if (values[j].Weight > pivot.Weight)
        {
            i++;    // increment index of smaller element
            swap(&values[i], &values[j]);
        }
        // Else if current weight is equal to pivot weight
        else if (values[j].Weight == pivot.Weight)
        {
            // Increasing order by phrase
            if (strcmp(values[j].Text, pivot.Text) < 0)
            {
                i++;
                swap(&values[i], &values[j]);
            }
        }
    }

    swap(&values[i + 1], &values[high]);
    return (i + 1);
}


// quickSort:
/* The main function that implements QuickSort
values --> Array to be sorted,
low  --> Starting index,
high  --> Ending index */
void quickSort(BSTValue *values, int low, int high)
{
    if (low < high)
    {
        // pi is partitioning index
        int pi = partition(values, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(values, low, pi - 1);
        quickSort(values, pi + 1, high);
    }
}


// skipRestOfInput:
// Inputs and discards the remainder of the current line for the 
// given input stream, including the EOL character(s).
void skipRestOfInput(FILE *stream)
{
    char restOfLine[256];
    int rolLength = sizeof(restOfLine) / sizeof(restOfLine[0]);

    fgets(restOfLine, rolLength, stream);
}


// getFileName: 
// inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be opened, an
// error message is output and the program is exited.
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


// BuildTree:
// Inputs data from file, stores in a BST, and returns tree.
BST *BuildTree(char* filename)
{
    long long weight;

    BST *tree = BSTCreate();

    FILE *infile = fopen(filename, "r");


    // fscanf(infile, "%lld", &weight);
    while (fscanf(infile, "%lld", &weight) != EOF)
    {
        char text[512];
        int textsize = sizeof(text) / sizeof(text[0]);
        fgets(text, textsize, infile);
        text[strcspn(text, "\r\n")] = '\0';  // strip EOL char(s):
        char* cp = text;

        while (*cp == ' '|| *cp == '\t')
            cp++;

        // store (key, value) into a BST value struct to insert:
        BSTValue  value;
        value.Text = (char *)malloc((strlen(text) + 1) * sizeof(char));
        strcpy(value.Text, cp);

        value.Weight = weight;

        // now that we have (key, value) pair, call BSTInsert to 
        // copy this (key, value) pair into a new node of the tree
        BSTInsert(tree, value.Text, value);
    }

    fclose(infile);

    return tree;
}


// countMatches:
// Counts the number of matches of given key in sub-tree
int countMatches(BSTNode *root, BSTKey key)
{
    if (root == NULL)
        return 0;

    else if(BSTCompareKeys(key, root->Key, 1) == 0)
        return 1 + countMatches(root->Left, key) + countMatches(root->Right, key);

    return 0 + countMatches(root->Left, key) + countMatches(root->Right, key);
}


// statsFunction:
// Function that handles "stats" command
void statsFunction(BST *tree)
{
    // Output the count of the generated tree
    int count = BSTCount(tree->Root);
    printf("**Tree count:  %d\n", count);

    // Output the height of the generated tree
    int height = BSTHeight(tree);
    printf("**Tree Height: %d\n", height);
}


// addFunction:
// Function that handles "add weight text" command
void addFunction(BST *tree, long long weight, BSTKey text)
{
    // Assign given weight and text to 
    // newly allocated BSTValue
    BSTValue  value;
    value.Text = (char *)malloc((strlen(text) + 1) * sizeof(char));
    strcpy(value.Text, text);
    value.Weight = weight;

    // Try to insert the value into the tree
    if (!BSTInsert(tree, value.Text, value))
        printf("**Not added...\n");
    else
        printf("**Added\n");
}


// findFunction:
// Function that handles "find key" command
void findFunction(BST *tree, BSTKey key)
{
    int flag = 0;

    // Search the tree and get back the resulting node
    BSTNode *node = BSTSearch(tree, key, flag);

    // Display result
    if (node != NULL)
        printf("%s: %lld\n", node->Value.Text, node->Value.Weight);
    else
        printf("**Not found...\n");
}


// suggestFunction:
// Function that handles the "suggest phrase" command
void suggestFunction(BST *tree, BSTKey phrase, int k)
{
    // Search phrase
    int flag = 1;

    BSTNode *node = BSTSearch(tree, phrase, flag);

    // Output search result
    if (node == NULL)
    {
        printf("**No suggestions...\n");
        return;
    }

    printf("** [Sub-tree root:  (%s,%lld)]\n", node->Value.Text, node->Value.Weight);

    // Count and output sub-tree nodes
    int count = BSTCount(node);
    printf("** [Sub-tree count: %d]\n", count);

    // Search sub-tree for phrase matches
    int matches = countMatches(node, phrase);

    // Output number of matches
    printf("** [Num matches:    %d]\n", matches);

    // Store matching values from sub-tree by going through
    // left-to-right into an array
    BSTValue *values;
    values = BSTStoreValues(node, phrase, count);

    // Sort the values array using quicksort
    quickSort(values, 0, matches);

    // Output the suggestions in order
    for (int i = 0; i < k; i++)
    {
        if (values[i].Text != NULL)
            printf("%s: %lld\n", values[i].Text, values[i].Weight);
        else
            break;
    }

    // Free memory of array
    free(values);
}

int main()
{
    char *filename;
    char  cmd[64];
    char  text[512];
    int   textsize = sizeof(text) / sizeof(text[0]);

    printf("** Starting Autocomplete **\n");

    filename = getFileName();

    // Build a tree from the given file
    BST* Tree = BuildTree(filename);

    // now interact with user:
    //
    printf("** Ready **\n");

    scanf("%s", cmd);

    while (strcmp(cmd, "exit") != 0)
    {
        if (strcmp(cmd, "stats") == 0)
            // Call stats function
            statsFunction(Tree);

        else if (strcmp(cmd, "add") == 0)
        {
            long long weight;
            char part2[512];
            int part2size = sizeof(part2) / sizeof(part2[0]);

            // add weight text
            scanf("%lld %s", &weight, text);
            fgets(part2, part2size, stdin);
            part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
            strcat(text, part2);
            text[strcspn(text, "\r\n")] = '\0';

            // Call add function
            addFunction(Tree, weight, text);
        }
        else if (strcmp(cmd, "find") == 0)
        {
            char part2[512];
            int  part2size = sizeof(part2) / sizeof(part2[0]);

            // find text
            scanf("%s", text);
            fgets(part2, part2size, stdin);
            part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
            strcat(text, part2);
            text[strcspn(text, "\r\n")] = '\0';

            // Call find function
            findFunction(Tree, text);
        }
        else if (strcmp(cmd, "suggest") == 0)
        {
            int  k;
            char part2[512];
            int  part2size = sizeof(part2) / sizeof(part2[0]);

            // suggest k text
            scanf("%d %s", &k, text);
            fgets(part2, part2size, stdin);
            part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
            strcat(text, part2);

            // Call suggest function
            suggestFunction(Tree, text, k);
        }
        else 
            printf("**unknown cmd, try again...\n");

        scanf("%s", cmd);
    }

    printf("** Done **\n");

    return 0;
}