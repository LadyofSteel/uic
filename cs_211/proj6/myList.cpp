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
  MyNode<DataType> *temp = head;

  while (temp != NULL) {
    head = temp->getNext();
    delete[] temp;
  }
}

template<class DataType>
bool MyList<DataType>::isEmpty() const
{
  return ( size <= 0 );
}

template<class DataType>
void MyList<DataType>::reset()
{
}

template<class DataType>
bool MyList<DataType>::contains(const DataType data)
{
  // Check if list contains given data
  return false;
}

template<class DataType>
void MyList<DataType>::add(DataType data)
{
  MyNode<DataType> *newNode = new MyNode<DataType>(data, NULL, NULL);

  if (tail == NULL) {
    setHead(newNode);
    setTail(newNode);
    newNode->setPrevious(NULL);
  } else {
    getTail()->setNext(newNode);
    newNode->setPrevious(getTail());
    setTail(newNode);
  }
}

template<class DataType>
void MyList<DataType>::remove(DataType data)
{
  MyNode<DataType> *current = getHead();

  while (current != NULL) {
    if (current->getData() == data) {
      if (current->getPrevious() == NULL &&
          current->getNext() == NULL) { // Only one node in list

        setHead(NULL);
        setTail(NULL);
        //freeNode(current);
      } else if (current->getPrevious() == NULL) { // Current is at head
        setHead(current->getNext());
        getHead()->setPrevious(NULL);
        //freeNode(current);
      } else if (current->getNext() == NULL) { // Current is at tail
        setTail(current->getPrevious());
        getTail()->setNext(NULL);
        //freeNode(current);
      } else {
        current->getPrevious()->setNext(current->getNext());
        current->getNext()->setPrevious(current->getPrevious());
        //freeNode(current);
      }
    }
    
    current = current->getNext();
  }
}

// Explicit instantiation for templates
template class MyList<int>;
template class MyList<Airport>;
template class MyList<string>;
