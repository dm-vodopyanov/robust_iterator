#ifndef NODE_H_
#define NODE_H_

template <typename T> class Node {
public:
    T* data;
    Node<T>* prev;
    Node<T>* next;

    explicit Node(T* _data = 0) {
        data = _data;
        prev = nullptr;
        next = nullptr;
    }
};

#endif  // NODE_H_
