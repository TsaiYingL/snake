template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
    //initialize new node
    Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
};