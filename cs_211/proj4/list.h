/**
 *  @brief CS 211 Project 4
 *
 *  This file is used to create and use a linked-list
 *  for the waiting list.
 *
 *  @author Ammar Subei
*/

#ifndef LIST_H
#define LIST_H

/**
 *  @brief ListNode for each group in the list
*/
typedef struct ListNode
{
  char *name;             ///< String name of group
  int size;               ///< Integer value for the group size
  bool in_restaurant;     ///< Boolean if group is in restaurant
  struct ListNode *next;  ///< Pointer to the next group
} ListNode;

/**
 *  @brief List object
*/
typedef struct List
{
  ListNode *head; ///< Pointer to the head of the list
} List;

#endif /* LIST_H */
