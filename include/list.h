/*
MIT License

Copyright (c) 2018 Dmitry Vodopyanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef LIST_H_
#define LIST_H_

template <typename T>
class ListIterator;

template <typename T>
class Node;

template <typename T>
class List {
public:
    Node<T>* pRoot;
    Node<T>* pTail;

    List() : pRoot(nullptr), pTail(nullptr) {}

    ~List() {
        if (pRoot != nullptr) {
            Node<T>* tmp(pRoot);
            while (pRoot != nullptr) {
                tmp = pRoot->next;
                delete pRoot;
                pRoot = tmp;
            }
        }
    }

    void add(T* data) {
        auto tmp(new Node<T>(data));
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
        auto tmp(pRoot);
        while (tmp != nullptr) {
            if (tmp->data == data)
                return tmp;
            tmp = tmp->next;
        }
        return nullptr;
    }

    Node<T>* insert(T* key, T* data) {
        auto pKey(find(key));
        if (pKey) {
            auto pNode(new Node<T>(data));
            pNode->next = pKey->next;
            pKey->next = pNode;
            return pNode;
        }
        return nullptr;
    }

    T* get(int key) {
        auto tmp(pRoot);
        int i = 0;
        while (tmp != nullptr) {
            if (i == key)
                break;
            tmp = tmp->next;
            i++;
        }
        return (tmp != nullptr) ? tmp->data : nullptr;
    }

    T* get_prev(T* data) {
        auto iterator(new ListIterator<T>(this));

        T* prev = nullptr;
        while (!iterator->is_done()) {
            auto current = (T*)(iterator->next());
            if (current == data) {
                return prev;
            }
            prev = current;
        }
        return nullptr;
    }

    T* get_next(T* data) {
        auto iterator(new ListIterator<T>(this));
        if (data == nullptr) {
            return (iterator->is_done()) ? (T*)(iterator->next()) : nullptr;
        }
        while (iterator->is_done()) {
            auto current = (T*)(iterator->next());
            if (current == data) {
                return (iterator->is_done()) ? (T*)(iterator->next()) : nullptr;
            }
        }
        return nullptr;
    }

    int count() {
        auto tmp = pRoot;
        int count = 0;
        while (tmp != nullptr) {
            ++count;
            tmp = tmp->next;
        }
        return count;
    }

    bool remove(T* data) {
        auto pKey(find(data));
        if (pKey) {
            if (pKey == pRoot)
                pRoot = pKey->next;
            else {
                auto tmp = pRoot;
                while (tmp != nullptr) {
                    if (tmp->next == pKey) {
                        break;
                    }
                    tmp = tmp->next;
                }
                if (tmp) {
                    tmp->next = pKey->next;
                }
            }
            delete pKey;
            return true;
        }
        return false;
    }
};

#endif  // LIST_H_
