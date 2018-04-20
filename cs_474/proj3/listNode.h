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
    T getData() const { return data; }

  private:
    T data;                 ///< Node data
    ListNode<T> *next;      ///< Next node
    ListNode<T> *previous;  ///< Previous node
};
