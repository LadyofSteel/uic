/**
 *  @brief MyList definitions
 *
 *  @author Ammar Subei
*/

#include <string>

#include "myList.h"
#include "airport.h"

using std::string;

template<class DataType>
MyList<DataType>::MyList()
{
  setSize(0);
  head = NULL;
  tail = NULL;
}

template<class DataType>
MyList<DataType>::~MyList()
{
  MyNode<DataType> *temp = getHead();

  while (temp != NULL) {
    setHead(temp->getNext());
    delete temp;
  }
}

template<class DataType>
bool MyList<DataType>::isEmpty() const
{
  return ( getSize() <= 0 );

}

template<class DataType>
bool MyList<DataType>::contains(const DataType data)
{
  MyNode<DataType> *current = getHead();

  while (current != NULL) {
    if (current->getData() == data)
      return true;

    current = current->getNext();
  }

  return false;
}

template<class DataType>
MyNode<DataType>* MyList<DataType>::getNode(const DataType data)
{
  MyNode<DataType> *current = getHead();

  while (current != NULL) {
    if (current->getData() == data)
      return current;

    current = current->getNext();
  }

  return NULL;
}

template<class DataType>
void MyList<DataType>::add(DataType data)
{
  MyNode<DataType> *newNode = new MyNode<DataType>(data, NULL, NULL);

  if (tail == NULL) {
    setHead(newNode);
    setTail(newNode);
    newNode->setPrevious(NULL);
    setSize(getSize() + 1);
  } else {
    getTail()->setNext(newNode);
    newNode->setPrevious(getTail());
    setTail(newNode);
    setSize(getSize() + 1);
  }
}

template<class DataType>
bool MyList<DataType>::remove(DataType data)
{
  MyNode<DataType> *current = getHead();

  while (current != NULL) {
    if (current->getData() == data) {
      if (current->getPrevious() == NULL &&
          current->getNext() == NULL) { // Only one node in list

        setHead(NULL);
        setTail(NULL);
        setSize(getSize() - 1);

        delete current;
        return true;
      } else if (current->getPrevious() == NULL) { // Current is at head
        setHead(current->getNext());
        getHead()->setPrevious(NULL);
        setSize(getSize() - 1);

        delete current;
        return true;
      } else if (current->getNext() == NULL) { // Current is at tail
        setTail(current->getPrevious());
        getTail()->setNext(NULL);
        setSize(getSize() - 1);

        delete current;
        return true;
      } else {
        current->getPrevious()->setNext(current->getNext());
        current->getNext()->setPrevious(current->getPrevious());
        setSize(getSize() - 1);

        delete current;
        return true;
      }
    }
    
    current = current->getNext();
  }

  return false;
}

template<class DataType>
void MyList<DataType>::removeAll()
{
  MyNode<DataType> *current = getHead();

  while (current != NULL) {
    setHead(current->getNext());
    delete current;
  }

  setSize(0);
}

// Explicit instantiation for templates
template class MyList<int>;
template class MyList<Airport>;
template class MyList<string>;
