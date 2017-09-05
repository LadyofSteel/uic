#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SORT_BY_RATING 1
#define SORT_BY_REVIEWS 0


typedef struct MOVIE
{
    char  Name[512];
    int   ID;
    int   PubYear;
} MOVIE;


typedef MOVIE* BSTValue;
typedef int BSTKey;


typedef struct BSTNode
{
    BSTKey    Key;
    BSTValue  Value;
    struct BSTNode  *Left;
    struct BSTNode  *Right;
} BSTNode;

typedef struct BST
{
    BSTNode *Root;
} BST;

//
// BSTCreate: dynamically creates and returns an empty
// binary search tree:
//
BST *BSTCreate()
{
    BST *tree;

    tree = (BST *)malloc(sizeof(BST));
    tree->Root  = NULL;

    return tree;
}

//
// BSTCompareKeys: compares key1 and key2, returning
//   value < 0 if key1 <  key2
//   0         if key1 == key2
//   value > 0 if key1 >  key2
//
int BSTCompareKeys(BSTKey key1, BSTKey key2)
{
    if (key1 < key2)
        return -1;
    else if (key1 == key2)
        return 0;
    else
        return 1;
}

//
// BSTSearch: searches the binary search tree for a node containing the
// same key.  If a match is found, a pointer to the node is returned, 
// otherwise NULL is returned.
//
BSTNode *BSTSearch(BST *tree, BSTKey key)
{
    BSTNode *tempNode = (BSTNode*) malloc(sizeof(BSTNode));
    tempNode = tree->Root;

    while (tempNode != NULL)
    {
        if (BSTCompareKeys(key, tempNode->Key) < 0)
        {
            printf(">>Visiting %d: '%s'\n", tempNode->Key, tempNode->Value->Name);
            tempNode = tempNode->Left;
        }

        else if (BSTCompareKeys(key, tempNode->Key) > 0)
        {
            printf(">>Visiting %d: '%s'\n", tempNode->Key, tempNode->Value->Name);
            tempNode = tempNode->Right;
        }

        else
        {
            printf(">>Visiting %d: '%s'\n", tempNode->Key, tempNode->Value->Name);
            return tempNode;
        }
    }
    return NULL;
}

//
// BSTInsert: inserts the given (key, value) pair into the binary search
// tree.  Returns true (non-zero) if the insert was successful, returns 
// false (0) if the given key is already in the tree -- in which case the
// given (key, value) pair is not inserted.
//
int BSTInsert(BST *tree, BSTKey key, BSTValue value)
{
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->Left = NULL;
    newNode->Right = NULL;
    newNode->Key = key;
    newNode->Value = value;

    if (tree->Root == NULL)
    {
    tree->Root = newNode;
    return 1;
    }
    else
    {
        BSTNode *currNode = (BSTNode*) malloc(sizeof(BSTNode));
        currNode = tree->Root;

        while (currNode != NULL)
        {
            if (BSTCompareKeys(newNode->Key, currNode->Key) < 0)
            {
                if (currNode->Left == NULL)
                {
                    currNode->Left = newNode;
                    currNode = NULL;
                    return 1;
                }
                else
                    currNode = currNode->Left;
            }
            else if (BSTCompareKeys(newNode->Key, currNode->Key) > 0)
            {
                if (currNode->Right == NULL)
                {
                    currNode->Right = newNode;
                    currNode = NULL;
                    return 1;
                }
                else
                    currNode = currNode->Right;
            }
            else
                return 0;
        }
    }

    return 0;
}

//
// getFileName: inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be opened, an
// error message is output and the program is exited.
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

// Parses the line, stores the movie information,
// then returns the movie for later use
MOVIE* createMovie(char *line)
{
    line[strcspn(line, "\r\n")] = '\0';

    MOVIE *newMovie = (MOVIE *)malloc(sizeof(MOVIE));

    newMovie->ID = atoi(strtok(line, ","));

    char *temp = strtok(NULL, ",");
    strcpy(newMovie->Name, temp);

    newMovie->PubYear = atoi(strtok(NULL, ","));

    return newMovie;
}

// Stores each movie from the movies file into the given BST
void storeMovies(FILE *fp, BST *tree)
{
    char *line;
    size_t lineSize = 0;

    getline(&line, &lineSize, fp);   // Ignore first line

    while(fgets(line, lineSize, fp))
    {
        // Create a movie object with the info from line
        MOVIE *movie = createMovie(line);
        // Insert that movie object into the BST
        BSTInsert(tree, movie->ID, movie);
    }
}


// inputs and discards the remainder of the current line for the 
// given input stream, including the EOL character(s):
void skipRestOfInput(FILE *stream)
{
    char restOfLine[256];
    int rolLength = sizeof(restOfLine) / sizeof(restOfLine[0]);

    fgets(restOfLine, rolLength, stream);
}


int main()
{
    // Get filenames from the user/stdin:
    char *MoviesFileName = getFileName();

    // Open movies file 
    FILE *fp;
    fp = fopen(MoviesFileName, "r");

    if (!fp)
        exit(EXIT_FAILURE);

    // Create tree
    BST *tree = BSTCreate();

    // Store movies from movies file into the tree
    storeMovies(fp, tree);

    // We're done with the movies file
    fclose(fp);

    // Now we search for movieID
    int key = 0;
    fscanf(stdin, "%d", &key);

    // Now we search for the user input key, and store the result
    BSTNode *node = BSTSearch(tree, key);

    // If movie was not found
    if (node == NULL)
        printf("Movie %d: not found\n", key);
    // If movie was found
    else  
        printf("Movie %d: '%s'\n", key, node->Value->Name);

    return 0;
}
