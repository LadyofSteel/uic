/**
 *  @brief CS 211 Project 4
 *
 *  This file implements the doubly linked-list for the waiting list.
 *
 *  @author Ammar Subei
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

List* createList()
{
  List *new_list = (List *) malloc( sizeof(List) );
  new_list->head = NULL;
  new_list->tail = NULL;

  return new_list;
}

void freeNode(ListNode *node)
{
  free(node->name);
  free(node);
}

void clearList(List *list)
{
  ListNode *temp = list->head;

  while (temp != NULL) {
    list->head = temp->next;
    freeNode(temp);
  }
}

void addToList(List *list, char *new_name, int new_size, bool waiting, bool debug)
{
  ListNode *new_node = (ListNode *) malloc( sizeof(ListNode) );
  new_node->name = (char *) malloc( sizeof(char) * strlen(new_name));
  new_node->name = strcpy(new_node->name, new_name);
  new_node->size = new_size;
  new_node->in_restaurant = waiting;
  new_node->next = NULL;

  if (list->tail == NULL) {
    list->head = new_node;
    list->tail = new_node;
    new_node->previous = NULL;
  } else {
    list->tail->next = new_node;
    new_node->previous = list->tail;
    list->tail = new_node;
  }

  if (debug)
    printf("DEBUG: new group %s added to tail of the list\n", new_name);
}

bool doesNameExist(List *list, char *target_name)
{
  ListNode *current = list->head;

  while (current != NULL) {
    if ( !strcmp(current->name, target_name) )
      return true;
    
    current = current->next;
  }

  return false;
}

bool updateStatus(List *list, char *target_name, bool new_status, bool debug)
{
  ListNode *current = list->head;

  while (current != NULL) {
    if (debug)
      printf("DEBUG: checking group %s\n", current->name);

    if ( !strcmp(current->name, target_name) ) {
      if (current->in_restaurant != new_status) {
        current->in_restaurant = new_status;
        return true;
      } else {
        return false;
      }
    }
    
    current = current->next;
  }

  return false;
}

char* retrieveAndRemove(List *list, int table_size, bool debug)
{
  ListNode *current = list->head;
  char *node_name;

  while (current != NULL) {
    if (debug)
      printf("DEBUG: checking group %s\n", current->name);

    if (current->size <= table_size) {
      if (current->in_restaurant == true) {
        node_name = (char *) malloc( sizeof(char) * strlen(current->name) );
        node_name = strcpy(node_name, current->name);

        if (current->previous == NULL &&
            current->next == NULL) { // Only one node in list
          if (debug)
            printf("DEBUG: Retrieving the only group in the list\n");

          list->head = NULL;
          list->tail = NULL;
          freeNode(current);
        } else if (current->previous == NULL) { // Current is at head
          if (debug)
            printf("DEBUG: Retrieving the group at the head of the list\n");

          list->head = current->next;
          list->head->previous = NULL;
          freeNode(current);
        } else if (current->next == NULL) { // Current is at tail
          if (debug)
            printf("DEBUG: Retrieving the group at the tail of the list\n");

          list->tail = current->previous;
          list->tail->next = NULL;
          freeNode(current);
        } else {
          if (debug)
            printf("DEBUG: Retrieving the group somewhere in the middle of the list\n");

          current->previous->next = current->next;
          freeNode(current);
        }

        return node_name;
      }
    }
    
    current = current->next;
  }

  return NULL;
}

int countGroupsAhead(List *list, char *target_name, bool debug)
{
  ListNode *current = list->head;
  int node_count = 0;

  while (current != NULL) {
    if (debug)
      printf("DEBUG: checking group %s\n", current->name);

    if ( !strcmp(current->name, target_name) )
      return node_count;

    node_count++;
    current = current->next;
  }

  // Group name not in the list
  return -1;
}

void displayGroupSizeAhead(List *list, char *target_name, bool debug)
{
  ListNode *current = list->head;

  while (current != NULL) {
    if (debug)
      printf("DEBUG: checking group %s\n", current->name);

    if ( !strcmp(current->name, target_name) )
      return;

    printf("Group size: %d\n", current->size);

    current = current->next;
  }
}

void displayListInformation(List *list, bool debug)
{
  ListNode *current = list->head;

  if (list->head == NULL) {
    printf("Waiting list is empty! No information to provide.\n");
    return;
  }

  printf("Displaying list information.\n\n");

  while (current != NULL) {
    if (debug)
      printf("DEBUG: checking group %s\n", current->name);

    printf("Group Name:           %s\n", current->name);
    printf("Group Size:           %d\n", current->size);
    if (current->in_restaurant)
      printf("Group In-Restaurant:  True\n\n");
    else
      printf("Group In-Restaurant:  False\n\n");

    current = current->next;
  }
}
