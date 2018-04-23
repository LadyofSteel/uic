/**
 *  @brief ListNode class header file
 *
 *  @author Ammar Subei
*/

#pragma once

/**
 *  @brief ListNode for each group in the list
*/
template<typename T>
class ListNode
{
  public:
    /**
     *  @brief Default constructor
    */
    ListNode(T input)
    {
      data = input;
      next = nullptr;
      previous = nullptr;
    }

    /**
     *  @brief Getter for node data
    */
    T getData()                 const { return data; }

    /**
     *  @brief Getter for next node
    */
    ListNode* getNext()         const { return next; }

    /**
     *  @brief Getter for previous node
    */
    ListNode* getPrevious()     const { return previous; }

    /**
     *  @brief Setter for next node
    */
    void setNext(ListNode* node)      { next = node; }

    /**
     *  @brief Setter for previous node
    */
    void setPrevious(ListNode* node)  { previous = node; }

  private:
    T data;                 ///< Node data
    ListNode<T> *next;      ///< Next node
    ListNode<T> *previous;  ///< Previous node
};
