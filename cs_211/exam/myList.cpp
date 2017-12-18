/**
 *  @brief MyList definitions
 *
 *  @author Ammar Subei
*/

#include <iostream>

#include "myList.h"

template<class DataType>
MyList<DataType>::MyList()
{
  setSize(0);
  setHead(nullptr);
  setTail(nullptr);
}

template<class DataType>
bool MyList<DataType>::isEmpty() const
{
  return ( getLength() <= 0 );
}

template<class DataType>
bool MyList<DataType>::doesValueExist(const DataType data)
{
  Node<DataType> *current = getHead();

  while (current != nullptr) {
    if (current->getData() == data)
      return true;

    current = current->getNext();
  }

  return false;
}

template<class DataType>
DataType MyList<DataType>::getNthValue(const int index)
{
  Node<DataType> *current = getHead();
  int currentIndex = 0;

  while (current && (currentIndex < index)) {
    currentIndex++;
    current = current->getNext();
  }

  if (current) {
    return current->getData();
  } else {
    return -999;
  }
}

template<class DataType>
void MyList<DataType>::add(DataType data)
{
  Node<DataType> *newNode = new Node<DataType>(data);

  if ( doesValueExist(data) ) {
    return;
  }

  if (getTail() == nullptr) {
    setHead(newNode);
    setTail(newNode);
    newNode->setPrevious(nullptr);
    setSize(getLength() + 1);
  } else {
    getTail()->setNext(newNode);
    newNode->setPrevious(getTail());
    setTail(newNode);
    setSize(getLength() + 1);
  }
}

template<class DataType>
void MyList<DataType>::remove(DataType data)
{
  Node<DataType> *current = getHead();

  while (current) {
    if (current->getData() == data) {
      if (current->getPrevious() == nullptr &&
          current->getNext() == nullptr) { // Only one node in list

        setHead(nullptr);
        setTail(nullptr);
        setSize(getLength() - 1);

        delete current;
        return;
      } else if (current->getPrevious() == nullptr) { // Current is at head
        setHead(current->getNext());
        getHead()->setPrevious(nullptr);
        setSize(getLength() - 1);

        delete current;
        return;
      } else if (current->getNext() == nullptr) { // Current is at tail
        setTail(current->getPrevious());
        getTail()->setNext(nullptr);
        setSize(getLength() - 1);

        delete current;
        return;
      } else {
        current->getPrevious()->setNext(current->getNext());
        current->getNext()->setPrevious(current->getPrevious());
        setSize(getLength() - 1);

        delete current;
        return;
      }
    }
    
    current = current->getNext();
  }
}

template<class DataType>
void MyList<DataType>::removeAll()
{
  Node<DataType> *temp;

  while (getHead()) {
    temp = getHead();
    setHead(temp->getNext());
    delete temp;
  }

  setSize(0);
  setHead(nullptr);
  setTail(nullptr);
}


template<class DataType>
void MyList<DataType>::showList()
{
  Node<DataType> *current = getHead();

  while (current) {
    std::cout << current->getData() << std::endl;
    current = current->getNext();
  }
}

// Explicit instantiation for templates
template class MyList<int>;
