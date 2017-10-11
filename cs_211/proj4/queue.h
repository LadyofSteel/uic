/**
 *  @brief CS 211 Project 4
 *
 *  This file is used to create and use a linked-list
 *  as a queue object.
 *
 *  @author Ammar Subei
*/

#ifndef QUEUE_H
#define QUEUE_H

/**
 *  @brief StackNode for each stack element
*/
typedef struct QueueNode
{
  int x_pos;              //!< Integer value for x position
  int y_pos;              //!< Integer value for y position
  struct QueueNode *next; //!< Pointer to the next StackNode object
} QueueNode;

/**
 *  @brief Struct for a stack object
*/
typedef struct Queue
{
  QueueNode *head; //!< Pointer to the head of the stack
} Queue;

#endif /* QUEUE_H */
