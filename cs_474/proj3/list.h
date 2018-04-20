/**
 *  @brief Linked List class header file
 *
 *  @author Ammar Subei
*/

#pragma once

#include "listNode.h"

template<typename T>
class List
{
  public:
    List();
    List(const int size);
    ~List();
    bool isEmpty();
    T at(const int index);
    void add(T newItem);
    void remove(const int index);
    void removeAll();

  private:
    ListNode<T> *head; ///< Pointer to the head of the list
    ListNode<T> *tail; ///< Pointer to the tail of the list
};
