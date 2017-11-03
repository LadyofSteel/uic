/**
 *  @brief MyStack definitions
 *
 *  This file is used to define the MyStack object functions.
 *
 *  @author Ammar Subei
*/

#include <algorithm>

#include "mystack.h"

template<class DataType>
MyStack<DataType>::MyStack()
{
  setCapacity(2);
  setSize(0);
  data = new DataType[capacity];
}

template<class DataType>
MyStack<DataType>::~MyStack()
{
  delete[] data;
}

template<class DataType>
bool MyStack<DataType>::isEmpty() const
{
  return ( size <= 0 );
}

template<class DataType>
bool MyStack<DataType>::isFull() const
{
  return ( size == capacity );
}

template<class DataType>
void MyStack<DataType>::resize()
{
  capacity += 2;

  DataType *temp_data = new DataType[capacity];

  for (int i = 0; i < size; i++)
    temp_data[i] = data[i];

  delete[] data;
  data = temp_data;
}

template<class DataType>
void MyStack<DataType>::reset()
{
  delete[] data;

  size = 0;
  capacity = 2;
  data = new DataType[capacity];
}

template<class DataType>
void MyStack<DataType>::push(const DataType value)
{
  if ( isFull() )
    resize();

  data[size] = value;
  size++;
}

template<class DataType>
bool MyStack<DataType>::pop()
{
  if ( isEmpty() )
    return false;

  size--;
  return true;
}

template<class DataType>
DataType MyStack<DataType>::top() const
{
  if ( !isEmpty() )
    return ( data[size - 1] );

  return -1;
}

// Explicit instantiation for templates
template class MyStack<int>;
template class MyStack<char>;
