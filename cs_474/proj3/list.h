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
    List() : head(nullptr), tail(nullptr), size(0) {}

    List(const int inputSize) : head(nullptr), tail(nullptr), size(inputSize)
    {
      for (int i = 0; i < inputSize; i++) {
        this->add( T() );
      }
    }

    ~List()
    {
      ListNode<T> *current = this->head;

      while (current != nullptr) {
        ListNode<T> *temp = current;
        current = current->getPrevious();
        delete temp;
      }
    }

    int getSize() const
    {
      return size;
    }

    void setSize(const int newSize)
    {
      size = newSize;
    }

    bool isEmpty() const
    {
      return (head == nullptr) && (tail == nullptr);
    }

    T at(const int index)
    {
      ListNode<T> *current = head;
      for (int i = 0; i < index; i++) {
        current = current->getNext();
      }

      return current->getData();
    }

    void add(T newItem)
    {
      ListNode<T> *newNode = new ListNode<T>(newItem);

      if ( isEmpty() ) {
        head = newNode;
        tail = newNode;
      } else {
        tail->setNext(newNode);
        newNode->setPrevious(tail);
        tail = newNode;
      }

      setSize( getSize() + 1);
    }

    void remove(const int index) {}

    void removeAll() {}

  private:
    ListNode<T> *head;  ///< Pointer to the head of the list
    ListNode<T> *tail;  ///< Pointer to the tail of the list
    int size;           ///< Current size of the list
};
