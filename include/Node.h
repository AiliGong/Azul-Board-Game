#ifndef NODE_H
#define NODE_H

#include "Tile.h"

template<typename T>
class Node {
public:

    Node(T value);
    Node(T value, Node<T>* next);
    void setNext(Node<T>* next);
    T getValue() const;
    Node<T>* getNext() const;

private:
    T  value;
    Node<T>*  next;
};

template<typename T>
Node<T>::Node(T value) {
    this->value = value;
    next = nullptr;
}
 

template<typename T>
Node<T>::Node(T value, Node<T>* next){
    this->value = value;
    this->next = next;
}  

template<typename T>
void Node<T>::setNext(Node<T>* next) {
    this->next = next;
}

template<typename T>
T Node<T>::getValue() const {
    return value;
}

template<typename T>
Node<T>* Node<T>::getNext() const {
    return next;
}

#endif //NODE_H