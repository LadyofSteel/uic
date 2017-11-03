/**
 *  @brief MyStack class header
 *
 *  @author Ammar Subei
*/

#pragma once

/**
 *  @brief Templated class for the stack structure
 *
 *  This class is templated to help handle dynamic data types.
*/
template<class DataType>
class MyStack
{
  private:
    int size;       ///< Stack current size
    int capacity;   ///< Stack capacity
    DataType *data; ///< Stack data

  public:
    /**
     *  @brief Default constructor
    */
    MyStack();

    /**
     *  @brief Destructor
    */
    ~MyStack();

    /**
     *  @brief Getter for size
     *
     *  @return int current size
    */
    int getSize()               const { return size; }

    /**
     *  @brief Getter for capacity
     *
     *  @return int current capacity
    */
    int getCapacity()           const { return capacity; }

    /**
     *  @brief Setter for size
     *
     *  @param int new size
    */
    void setSize(const int value)     { size = value; }

    /**
     *  @brief Setter for capacity
     *
     *  @param int new capacity
    */
    void setCapacity(const int value) { capacity = value; }

    /**
     *  @brief Checks if the stack is empty
     *
     *  @return bool is empty
    */
    bool isEmpty() const;

    /**
     *  @brief Checks if the stack is full
     *
     *  @return bool is full
    */
    bool isFull() const;

    /**
     *  @brief Resizes the stack
     *
     *  The resizing is simply done by incrementing the capacity
     *  by 2 and reallocating memory for the data.
    */
    void resize();

    /**
     *  @brief Resets the stack
    */
    void reset();

    /**
     *  @brief Pushes data into stack
     *
     *  @param DataType data to push
    */
    void push(const DataType value);

    /**
     *  @brief Pops the stack
     *
     *  @return bool pop successful
    */
    bool pop();

    /**
     *  @brief Gets top element from stack
     *
     *  Access the top element from the given stack.
     *  If the stack is empty, it just returns.
     *
     *  @return DataType data at top of the stack
    */
    DataType top() const;
};
