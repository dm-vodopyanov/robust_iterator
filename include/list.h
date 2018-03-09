#ifndef LIST_H_
#define LIST_H_

template <typename T> class ListIterator;
template <typename T> class Node;

template <typename T> class List {
public:
    Node<T>* pRoot;
    Node<T>* pTail;

    List() {
        pRoot = nullptr;
        pTail = nullptr;
    }

    ~List() {
        if (pRoot != nullptr) {
            Node<T>* tmp = pRoot;
            while (pRoot != nullptr) {
                tmp = pRoot->next;
                delete pRoot;
                pRoot = tmp;
            }
        }
    }

    void add(T* data) {
        auto tmp = new Node<T>(data);
        if (pRoot == nullptr) {
            pRoot = pTail = tmp;
        }
        else {
            tmp->prev = pTail;
            pTail->next = tmp;
            pTail = tmp;
        }
    }

    Node<T>* find(T* data) {
        Node<T>* tmp = pRoot;
        while (tmp != nullptr) {
            if (tmp->data == data)
                return tmp;
            tmp = tmp->next;
        }
        return nullptr;
    }

    Node<T>* insert(T* key, T* data) {
        Node<T>* pKey = find(key);
        if (pKey) {
            auto pNode = new Node<T>(data);
            pNode->next = pKey->next;
            pKey->next = pNode;
            return pNode;
        }
        return nullptr;
    }

    T* get(int key) {
        Node<T>* tmp = pRoot;
        int i = 0;
        while (tmp != nullptr) {
            if (i == key)
                break;
            tmp = tmp->next;
            i++;
        }
        return tmp->data;
    }

    T* get_prev(T* data) {
        Iterator<T>* iterator = new ListIterator<T>(this);

        T* prev = nullptr;
        while (!iterator->is_done()) {
            T* current = (T*)iterator->next();
            if (current == data) {
                return prev;
            }
            prev = current;
        }
        return nullptr;
    }

    T* get_next(T* data) {
        Iterator<T>* iterator = new ListIterator<T>(this);
        if (data == nullptr) {
            if (iterator->is_done()) {
                return (T*)iterator->next();
            }
            else {
                return nullptr;
            }
        }
        while (iterator->is_done()) {
            T* current = (T*)iterator->next();
            if (current == data) {
                if (iterator->is_done()) {
                    return (T*)iterator->next();
                }
                else {
                    return nullptr;
                }
            }
        }
        return nullptr;
    }

    int count() {
        Node<T>* tmp = pRoot;
        int count = 0;
        while (tmp != nullptr) {
            count++;
            tmp = tmp->next;
        }
        return count;
    }

    bool remove(T* data) {
        Node<T>* pKey = find(data);
        if (pKey) {
            if (pKey == pRoot)
                pRoot = pKey->next;
            else {
                Node<T>* tmp = pRoot;
                while (tmp != nullptr) {
                    if (tmp->next == pKey) {
                        break;
                    }
                    tmp = tmp->next;
                }
                tmp->next = pKey->next;
                if (tmp == pTail)
                    tmp = pTail;
            }
            delete pKey;
            return true;
        }
        return false;
    }
};

#endif  // LIST_H_
