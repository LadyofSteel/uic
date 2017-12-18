/**
 *  @brief List Node header file
 *
 *  @author Ammar Subei
 */

#pragma once

template<class DataType>
class Node
{
  private:
    DataType data;  ///< The actual data
    Node *next;     ///< Pointer to next node
    Node *previous; ///< Pointer to previous node

  public:
    /**
     *  @brief Default constructor
     *
     *  @param DataType initial data
     */
    Node(DataType data)
    {
      setData(data);
      setNext(nullptr);
      setPrevious(nullptr);
    }

    /**
     *  @brief Secondary constructor
     *
     *  @param DataType initial data
     *  @param Node next node
     *  @param Node previous node
     */
    Node(DataType data, Node *next, Node *previous)
    {
      setData(data);
      setNext(next);
      setPrevious(previous);
    }

    /**
     *  @brief Getter for data
     *
     *  @return DataType data
     */
    DataType getData()              const { return data; }

    /**
     *  @brief Getter for next node
     *
     *  @return Node* next node
     */
    Node* getNext()                 const { return next; }

    /**
     *  @brief Getter for previous node
     *
     *  @return Node* previous node
     */
    Node* getPrevious()             const { return previous; }

    /**
     *  @brief Setter for data
     *
     *  @param DataType new data
     */
    void setData(const DataType newData)  { data = newData; }

    /**
     *  @brief Setter for next node
     *
     *  @param Node* next node
     */
    void setNext(Node *node)              { next = node; }

    /**
     *  @brief Setter for previous node
     *
     *  @param Node* previous node
     */
    void setPrevious(Node *node)          { previous = node; }
};
