#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <stdexcept>
#include <iostream>
#include "Node.h"

//Makes the class generic; without templates you'd need a separate class for every type 
template <typename T>
class DoublyLinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
    
    public:
        DoublyLinkedList();
        DoublyLinkedList(const T& val);
        DoublyLinkedList(Node<T>* node);
        ~DoublyLinkedList(); // destructor. Automatically called when the object is destroyed 

        // Insertion
        void push_front(const T& val);
        void push_back(const T& val);

        // Removal
        T pop_front();
        T pop_back();

        // Access
        Node<T>* get_head() const;
        Node<T>* get_tail() const;

        // Utility
        int  get_size() const;
        bool is_empty() const;
        void clear();
        void print() const; //print out all vals in the ddl
        void print_reverse() const;
};

#endif