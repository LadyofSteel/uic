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

void addToList(List *list, char *new_name, int new_size, bool waiting)
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

bool updateStatus(List *list, char *target_name, bool new_status)
{
  ListNode *current = list->head;

  while (current != NULL) {
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

char* retrieveAndRemove(List *list, int table_size)
{
  ListNode *current = list->head;
  char *group_name;

  while (current != NULL) {
    if (current->size <= table_size) {
      if (current->in_restaurant == true) {
        group_name = (char *) malloc( sizeof(char) * strlen(current->name) );
        group_name = strcpy(group_name, current->name);

        if (current->previous != NULL) {
          current->previous->next = current->next;
          freeNode(current);
        } else {
          list->head = current->next;
          freeNode(current);
        }

        return group_name;
      }
    }
    
    current = current->next;
  }

  return "";
}

int countGroupsAhead(List *list, char *target_name)
{
  ListNode *current = list->head;
  int group_count = 0;

  while (current != NULL) {
    if ( !strcmp(current->name, target_name) )
      return group_count;

    group_count++;
    current = current->next;
  }

  // Group name not in the list
  return -1;
}

void displayGroupSizeAhead(List *list, char *target_name)
{
  ListNode *current = list->head;

  while (current != NULL) {
    if ( !strcmp(current->name, target_name) )
      return;

    printf("Group size: %d\n", current->size);

    current = current->next;
  }
}

void displayListInformation(List *list)
{
  ListNode *current = list->head;

  printf("Displaying list information.\n\n");

  while (current != NULL) {
    printf("Group Name:           %s\n", current->name);
    printf("Group Size:           %d\n", current->size);
    printf("Group In-Restaurant:  %d\n\n", current->in_restaurant);

    current = current->next;
  }
}
