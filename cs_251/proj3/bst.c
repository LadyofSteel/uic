/*bst.c*/

//
// Binary Search Tree ADT implementation file.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS251, Spring 2017
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bst.h"


// BSTCreate: dynamically creates and returns an empty
// binary search tree:
BST *BSTCreate()
{
    BST *tree;

    tree = (BST *)malloc(sizeof(BST));
    tree->Root = NULL;

    return tree;
}


// BSTCompareKeys: compares key1 and key2, returning
//   value < 0 if key1 <  key2
//   0         if key1 == key2
//   value > 0 if key1 >  key2
int BSTCompareKeys(BSTKey key1, BSTKey key2, int flag)
{
    if (flag == 0)
        return strcmp(key1, key2);

    return strncmp(key1, key2, strlen(key1));
}


// BSTSearch: searches the binary search tree for a node containing the
// same key.  If a match is found, a pointer to the node is returned, 
// otherwise NULL is returned.
BSTNode *BSTSearch(BST *tree, BSTKey key, int flag)
{
    BSTNode *cur = tree->Root;

    // search the tree to see if it contains a matching key:
    while (cur != NULL)
    {
        if (BSTCompareKeys(key, cur->Key, flag) == 0)  // found!
            return cur;

        else if (BSTCompareKeys(key, cur->Key, flag) < 0)  // smaller, go left:
            cur = cur->Left;

        else  // larger, go right:
            cur = cur->Right;
    }

    // if we get here, we fell out of the tree, and didn't find it:
    return NULL;
}


// BSTInsert: inserts the given (key, value) pair into the binary search
// tree.  Returns true (non-zero) if the insert was successful, returns 
// false (0) if the given key is already in the tree -- in which case the
// given (key, value) pair is not inserted.
int BSTInsert(BST *tree, BSTKey key, BSTValue value)
{
    BSTNode *prev = NULL;
    BSTNode *cur = tree->Root;

    // first we search the tree to see if it already contains key:
    while (cur != NULL)
    {
        if (BSTCompareKeys(key, cur->Key, 0) == 0)  // already in tree, failed:
            return 0;

        else if (BSTCompareKeys(key, cur->Key, 0) < 0)  // smaller, go left:
        {
            prev = cur;
            cur = cur->Left;
        }
        else  // larger, go right:
        {
            prev = cur;
            cur = cur->Right;
        }
    }

    // If we get here, tree does not contain key, so insert new node
    // where we fell out of tree:
    BSTNode *T = (BSTNode *)malloc(sizeof(BSTNode));
    T->Key = key;
    T->Value = value;
    T->Left = NULL;
    T->Right = NULL;

    // link T where we fell out of tree -- after prev:
    if (prev == NULL)  // tree is empty, insert @ root:
        tree->Root = T;

    else if (BSTCompareKeys(key, prev->Key, 0) < 0)  // smaller, insert to left:
        prev->Left = T;

    else  // larger, insert to right:
        prev->Right = T;

    return 1;  // success:
}


// BSTCount: returns # of nodes in the tree.
int BSTCount(BSTNode *root)
{
    if (root == NULL)
        return 0;

    return 1 + BSTCount(root->Left) + BSTCount(root->Right);
}


BSTValue *_BSTStoreValues(BSTNode *root, BSTValue *values, int *index, BSTKey key)
{
    int flag = 1;

    if (root == NULL)
        return values;

    values = _BSTStoreValues(root->Left, values, index, key);

    if (BSTCompareKeys(key, root->Key, flag) == 0)
    { 
        (*index) += 1;
        values[*index] = root->Value;
    }

    values = _BSTStoreValues(root->Right, values, index, key);

    return values;
}


// BSTStoreValues: traverses the tree inorder so as to yield the (key, value)
// pairs in sorted order by key.  Returns a dynamically-allocated array
// of size N, containing a copy of the value in each tree node.  The
// value N can be obtained by calling BSTCount().
BSTValue *BSTStoreValues(BSTNode *root, BSTKey key, int count)
{
    BSTValue *values = (BSTValue *)malloc(count * sizeof(BSTValue));

    int* index = (int*) malloc(sizeof(int));
    *index = -1;

    return _BSTStoreValues(root, values, index, key);
}


int _max2(int x, int y)
{
    return (x > y) ? x : y;
} 


int _BSTHeight(BSTNode *root) 
{
    if (root == NULL) 
        return -1;

    return 1 + _max2( _BSTHeight(root->Left),  _BSTHeight(root->Right) );
}


// Returns the height of given tree
int BSTHeight(BST *tree)
{
    return _BSTHeight(tree->Root);
}