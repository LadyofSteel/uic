/**
 *  @brief List node header file
 *
 *  @author Ammar Subei
 */
#pragma once

#include <stdio.h>

template <class DataType>
class MyNode
{
  private:
    DataType data;      ///< The actual data
    MyNode *next;       ///< Pointer to the next node
    MyNode *previous;   ///< Pointer to the previous node

  public:
    /**
     *  @brief Default constructor
     */
    MyNode()
    {
      next = NULL;
      previous = NULL;
    }

    /**
     *  @brief Secondary constructor
     */
    MyNode(DataType data, MyNode *next, MyNode *previous)
    {
      setData(data);
      setNext(next);
      setPrevious(previous);
    }

    /** *  @brief Getter for data
     *  @return DataType data
     */
    DataType getData()        const { return data; }

    /**
     *  @brief Getter for next node
     *  @return MyNode* next node
     */
    MyNode* getNext()         const { return next; }

    /**
     *  @brief Getter for previous node
     *  @return MyNode* previous node
     */
    MyNode* getPrevious()     const { return previous; }

    /**
     *  @brief Setter for data
     *  @return DataType new data
     */
    void setData(DataType newData)  { data = newData; }

    /**
     *  @brief Setter for next node
     *  @return MyNode* next node
     */
    void setNext(MyNode* node)      { next = node; }

    /**
     *  @brief Setter for previous node
     *  @return MyNode* previous node
     */
    void setPrevious(MyNode* node)  { previous = node; }
};
