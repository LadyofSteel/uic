/**
 *  @brief MyList header file
 *
 *  @author Ammar Subei
 */

#pragma once

#include "node.h"

template <class DataType>
class MyList
{
  private:
    int size;             ///< Current list size
    Node<DataType> *head; ///< Pointer to head of list
    Node<DataType> *tail; ///< Pointer to tail of list

  public:
    /**
     *  @brief Default constructor
     */
    MyList();

    /**
     *  @brief Getter for size
     *
     *  @return int current size
     */
    int getLength()               const { return size; }

    /**
     *  @brief Getter for head of list
     *
     *  @return MyListNode* head of list
     */
    Node<DataType>* getHead()     const { return head; }

    /**
     *  @brief Getter for tail of list
     *
     *  @return MyListNode* tail of list
     */
    Node<DataType>* getTail()     const { return tail; }

    /**
     *  @brief Setter for size
     *
     *  @param int new size
     */
    void setSize(const int value)       { size = value; }

    /**
     *  @brief Setter for list head
     *
     *  @param int new head
     */
    void setHead(Node<DataType> *node)  { head = node; }

    /**
     *  @brief Setter for list tail
     *
     *  @param int new tail
     */
    void setTail(Node<DataType> *node)  { tail = node; }

    /**
     *  @brief Checks if the list is empty
     *
     *  @return bool list is empty
     */
    bool isEmpty() const;

    /**
     *  @brief Checks if the list contains the given data
     *
     *  @param DataType data to check for
     *  @return bool list contains given data
     */
    bool doesValueExist(const DataType data);

    /**
     *  @brief Returns data at given index
     *
     *  @param int index to grab data from
     *  @return DataType data at given index
     */
    DataType getNthValue(const int index);

    /**
     *  @brief Adds data to list
     *  
     *  @param DataType data to add
     */
    void add(DataType data);

    /**
     *  @brief Removes data from list
     *  
     *  @param DataType data to remove
     */
    void remove(DataType data);

    /**
     *  @brief Resets the list
     */
    void removeAll();

    /**
     *  @brief Prints list data
     */
    void showList();
};
