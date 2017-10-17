/**
 *  @brief CS 211 Project 4
 *
 *  This file is used to create and use a doubly
 *  linked-list for the waiting list.
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
  char *name;                 ///< String name of group
  int size;                   ///< Integer value for the group size
  bool in_restaurant;         ///< Boolean if group is in restaurant
  struct ListNode *next;      ///< Pointer to the next group
  struct ListNode *previous;  ///< Pointer to the previous group
} ListNode;

/**
 *  @brief List object
*/
typedef struct List
{
  ListNode *head; ///< Pointer to the head of the list
  ListNode *tail; ///< Pointer to the tail of the list
} List;

/**
 *  @brief Creates a new list object
 *
 *  @return new List object
*/
List* createList();

/**
 *  @brief Frees one list node
 *
 *  @param ListNode object
*/
void freeNode(ListNode *node);

/**
 *  @brief Clears the given list
 *
 *  Deletes all groups in the given list.
 *  Does not delete the list itself.
 *
 *  @param List object
*/
void clearList(List *list);

/**
 *  @brief Adds new group to the list
 *
 *  @param List object
 *  @param string group name
 *  @param int group size
*/
void addToList(List *list, char *new_name, int new_size, bool waiting, bool debug);

/**
 *  @brief Checks if name is already taken
 *
 *  @param List object
 *  @param string group name
 *  @return bool if name already exists
*/
bool doesNameExist(List *list, char *target_name);

/**
 *  @brief Updates group status
 *
 *  @param List object
 *  @param string group name
 *  @param bool new status
 *  @return bool if group has same status
*/
bool updateStatus(List *list, char *target_name, bool new_status, bool debug);

/**
 *  @brief Retrieves group that fits table size
 *
 *  @param List object
 *  @param int table size
 *  @return string name of the group
*/
char* retrieveAndRemove(List *list, int table_size, bool debug);

/**
 *  @brief Counts number of groups ahead of given group
 *
 *  @param List object
 *  @param string group name
 *  @return int number of groups ahead
*/
int countGroupsAhead(List *list, char *target_name, bool debug);

/**
 *  @brief Displays group sizes ahead of given group
 *
 *  @param List object
 *  @param string group name
*/
void displayGroupSizeAhead(List *list, char *target_name, bool debug);

/**
 *  @brief Displays every group info in the list
 *
 *  @param List object
*/
void displayListInformation(List *list, bool debug);

#endif /* LIST_H */
