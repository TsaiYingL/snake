#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <stdexcept>

//Makes the class generic; without templates you'd need a separate class for every type 
template <typename T>
class DoublyLinkedList {
    private:
        struct Node {
            T data;
            Node* prev;
            Node* next;
            //initialize new node
            Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
        };

        Node* head;
        Node* tail;
        int size;
    
    public:
        DoublyLinkedList();
        DoublyLinkedList(Node* node);
        ~DoublyLinkedList(); // destructor. Automatically called when the object is destroyed 

        // Insertion
        void push_front(const T& val);
        void push_back(const T& val);

        // Removal
        T pop_front();
        T pop_back();

        // Access
        Node* get_head();
        Node* get_tail();

        // Utility
        int  get_size() const;
        bool is_empty() const;
        void clear();
        void print() const; //print out all vals in the ddl
        void print_reverse() const;
};

#endif