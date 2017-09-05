/*bst.h*/

//
// Binary Search Tree ADT header file.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS251, Spring 2017
//

// make sure this header file is #include exactly once:
#pragma once


//
// BST type declarations:
//
typedef char*  BSTKey;
typedef struct BSTValue
{
    BSTKey Text;
    long long Weight;
} BSTValue;

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
// BST API: function prototypes
//
BST *BSTCreate();
BSTNode *BSTSearch(BST *tree, BSTKey key, int flag);
BSTValue *BSTStoreValues(BSTNode *root, BSTKey key, int count);

int BSTInsert(BST *tree, BSTKey key, BSTValue value);
int BSTCount(BSTNode *root);
int BSTHeight(BST *tree);
int BSTCompareKeys(BSTKey key1, BSTKey key2, int flag);