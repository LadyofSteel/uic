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

typedef enum
{
  false,
  true
} bool;

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

/**
 *  @brief Adds new group to the list
 *
 *  @param List object
 *  @param string group name
 *  @param int group size
*/
void addToList(List *list, char *name, int size);

/**
 *  @brief Checks if name is already taken
 *
 *  @param List object
 *  @param string group name
 *  @return bool if name already exists
*/
bool doesNameExist(List *list, char *name);

/**
 *  @brief Updates group status
 *
 *  @param List object
 *  @param string group name
 *  @param bool new status
 *  @return bool if group has same status
*/
bool updateStatus(List *list, char *name, bool new_status);

/**
 *  @brief Retrieves group that fits table size
 *
 *  @param List object
 *  @param int table size
 *  @return string name of the group
*/
char* retrieveAndRemove(List *list, int table_size);

/**
 *  @brief Counts number of groups ahead of given group
 *
 *  @param List object
 *  @param string group name
 *  @return int number of groups ahead
*/
int countGroupsAhead(List *list, char *name);

/**
 *  @brief Displays group sizes ahead of given group
 *
 *  @param List object
 *  @param string group name
*/
void displayGroupSizeAhead(List *list, char *name);

/**
 *  @brief Displays every group info in the list
 *
 *  @param List object
*/
void displayListInformation(List *list);

#endif /* LIST_H */
