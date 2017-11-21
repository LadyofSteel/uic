/**
 *  @brief MyList header file
 *
 *  @author Ammar Subei
 */
#pragma once

#include "myNode.h"

template <class DataType>
class MyList
{
  private:
    int size;               ///< Current list size
    MyNode<DataType> *head; ///< Pointer to the head of the list
    MyNode<DataType> *tail; ///< Pointer to the head of the list

  public:
    /**
     *  @brief Default constructor
     */
    MyList();

    /**
     *  @brief Destructor
     */
    ~MyList();

    /**
     *  @brief Getter for size
     *  @return int current size
     */
    int getSize()           const { return size; }

    /**
     *  @brief Getter for head of list
     *  @return MyListNode* head of list
     */
    MyNode<DataType>* getHead()       const { return head; }

    /**
     *  @brief Getter for tail of list
     *  @return MyListNode* tail of list
     */
    MyNode<DataType>* getTail()       const { return tail; }

    /**
     *  @brief Setter for size
     *  @param int new size
     */
    void setSize(const int value) { size = value; }

    /**
     *  @brief Setter for list head
     *  @param int new head
     */
    void setHead(MyNode<DataType> *node)    { head = node; }

    /**
     *  @brief Setter for list tail
     *  @param int new tail
     */
    void setTail(MyNode<DataType> *node)    { tail = node; }

    /**
     *  @brief Checks if the list is empty
     *  @return bool list is empty
     */
    bool isEmpty() const;

    /**
     *  @brief Checks if list contains given data
     *  @param DataType data
     *  @return bool given data is in the list
    */
    bool contains(const DataType data);

    /**
     *  @brief Gets the node with given data
     *  @param DataType data
     *  @return MyNode node that holds the data
    */
    MyNode<DataType>* getNode(const DataType data);

    /**
     *  @brief Adds data to list
     *  @param DataType data to add
     */
    void add(DataType data);

    /**
     *  @brief Removes data from list
     *  @param DataType data to remove
     *  @return bool remove successful
     */
    bool remove(DataType data);

    /**
     *  @brief Removes all nodes from list
     */
    void removeAll();
};
