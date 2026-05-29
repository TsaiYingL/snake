#include "DoublyLinkedList.h"
#include "Position.h"
#include <iostream>

// ── Constructor / Destructor ──────────────────────────────────────

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
    : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const T& val) {
    Node<T>* node = new Node<T>(val);
    head = node;
    tail = node;
    size = 1;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(Node<T>* node) {
    if (!node) throw std::invalid_argument("argument cannot be NULL");
    head = node;
    tail = node;
    size = 1;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() { clear(); }

// ── Insertion ─────────────────────────────────────────────────────
template <typename T>
void DoublyLinkedList<T>::push_front(const T& val) {
    Node<T>* newNode = new Node<T>(val);

    if(!head) {
        head = tail = newNode;
    } else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }

    size++;
}

template <typename T>
void DoublyLinkedList<T>::push_back(const T& val) {
    Node<T>* newNode = new Node<T>(val);

    if(!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    size++;
}

// ── Removal ─────────────────────────────────────────────────────────
template <typename T>
T DoublyLinkedList<T>::pop_front() {
    if (!head) throw std::underflow_error("List is empty");

    size--;

    Node<T>* node = head;
    T val = node->data;
    head = node->next;
    delete node;

    if(head) { //check if there's remaining nodes in ddl if we remove head
        //still has nodes remaining
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }

    return val;
}

template <typename T>
//need this cause implementation is outside the class in a separate file
//so you must tell the compiler where it belongs
T DoublyLinkedList<T>::pop_back() {
    if (!head) throw std::underflow_error("List is empty");

    size--;

    Node<T>* node = tail;
    T val = node->data;
    tail = node->prev;
    delete node;

    if(tail) { //check if there's remaining nodes in ddl if we remove tail
        //still has nodes remaining
        tail->next = nullptr;
    } else {
        head = nullptr;
    }

    return val;
}

// ── Access ─────────────────────────────────────────────────────────
template <typename T>
//Because Node is a type that lives inside a template class —
//the compiler needs typename to know it's a type and not a variable or function.
auto DoublyLinkedList<T>::get_head() const -> Node<T>* {
    return head;
}

template <typename T>
auto DoublyLinkedList<T>::get_tail() const -> Node<T>* {
    return tail;
}

// ── Utility ─────────────────────────────────────────────────────────
template <typename T>
int  DoublyLinkedList<T>::get_size() const{
    return size;
}

template <typename T>
bool DoublyLinkedList<T>::is_empty() const {
    return size == 0;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    if (!head) return;

    while(head) {
        pop_front();
    }
}

template <typename T>
void DoublyLinkedList<T>::print() const {
    if (!head) throw std::underflow_error("List is empty");

    Node<T>* node = head;
    while (node) {
        std::cout << node->data;
        if (node->next) std::cout << " -> ";
        node = node->next;
    }

    std::cout << "\n";
}


template <typename T>
void DoublyLinkedList<T>::print_reverse() const {
    if (!tail) throw std::underflow_error("List is empty");

    Node<T>* node = tail;
    while (node) {
        std::cout << node->data;
        if (node->prev) std::cout << " -> ";
        node = node->prev;
    }

    std::cout << "\n";
}

// ── Explicit instantiations ───────────────────────────────────────
template class DoublyLinkedList<int>;
template class DoublyLinkedList<float>;
template class DoublyLinkedList<double>;
template class DoublyLinkedList<Position>;
template class DoublyLinkedList<std::string>;