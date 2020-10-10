#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdexcept>
#include "Node.h"

template<typename T>
class LinkedList {
private:
  Node<T>* head;
  unsigned int size;

public:
  LinkedList();
  LinkedList(const LinkedList& other);
  ~LinkedList();
  void clear();

  unsigned int getSize() const;
  Node<T>* getHead() const;

  void add_front(const T value);
  void add_back(const T value);

  void remove_front();
  void remove_back();

};
template<typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    size = 0;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {

    if (other.head == nullptr) {
        head = nullptr;
    }
    else {
        head = new Node<T>(other.head->getTile());
        Node<T> *current = head;
        Node<T> *otherHead = other.head;
        Node<T> *temp = otherHead;
        while (temp->getNext() != nullptr) {
            current->setNext(new Node<T>(temp->getNext()->getTile()));
            temp = temp->getNext();
            current = current->getNext();
        }
    }
}

template<typename T>
LinkedList<T>::~LinkedList(){
    clear();
}

template<typename T>
void LinkedList<T>::clear(){
    while (head != nullptr) {
      remove_front();
   }
}

template<typename T>
unsigned int LinkedList<T>::getSize() const {
    return size;
}

template<typename T>
Node<T>* LinkedList<T>::getHead() const {
    return head;
}

template<typename T>
void LinkedList<T>::add_front(T value) {
    head = new Node<T>(value, head);
    ++this->size;
}

template<typename T>
void LinkedList<T>::add_back(T value){

    if (head == nullptr)
        head = new Node<T>(value);
    else {
        Node<T>* temp = head;
        while (temp->getNext() != nullptr) {
            temp = temp->getNext();
        }
        temp->setNext(new Node<T>(value));
        temp = nullptr;
    }

    ++this->size;
}

template<typename T>
void LinkedList<T>::remove_front(){
    //empty list
    if (head == nullptr)
        throw new std::logic_error("Attempted to remove item from empty list");

    Node<T>* temp = head;

    if (head->getNext() == nullptr) {   //only one node
        delete head;
        head = nullptr;
    } else {                            //two or more nodes
        head = head->getNext();
        delete temp;
        temp = nullptr;
    }

    --this->size;
}

template<typename T>
void LinkedList<T>::remove_back(){

    //empty list
    if (head == nullptr)
        throw new std::logic_error("Attempted to remove item from empty list");

    if (head->getNext() == nullptr) {       //only one node
        delete head;
        head = nullptr;
    } else {
        Node<T>* temp = head;
        while(temp->getNext()->getNext() != nullptr) {
            temp = temp->getNext();
        }

        delete temp->getNext();
        temp->setNext(nullptr);
    }

    --this->size;
}

#endif  // LINKEDLIST_H
