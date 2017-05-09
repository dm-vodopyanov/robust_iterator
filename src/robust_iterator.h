#pragma once

#include <stack>
#include <map>
#include <vector>

using namespace std;

template <typename T> class Component;

// ==========================================================================
// Iterator class
// ==========================================================================
template <typename T> class Iterator {
public:
    virtual Component<T>* next() = 0;
    virtual bool isDone() = 0;

    Iterator() {}
    virtual ~Iterator() {}
};

// ==========================================================================
// Component class
// ==========================================================================
template <typename T> class Component {
public:
    virtual Iterator<T>* create_iterator() = 0;
    virtual bool is_composite() = 0;
    virtual string to_string() = 0;

    Component() {}
    virtual ~Component() {}
};

// ==========================================================================
template <typename T> class Group;

// ==========================================================================
// RobustIterator class
// ==========================================================================
template <typename T> class RobustIterator : public Iterator<T> {
public:
    Component<T>* owner = nullptr;

    virtual Component<T>* next() = 0;
    virtual bool isDone() = 0;
    virtual void notify_remove(Component<T>* item) = 0;

    virtual Component<T>* get_owner() {
        return owner;
    }

    virtual void unsubscribe() {
        if (owner->is_composite()) {
            Group<T>* group = (Group<T>*)owner;
            group->unsubscribe(this);
        }
    }

    RobustIterator() {}
};

// ==========================================================================
// NullIterator class
// ==========================================================================
template <typename T> class NullIterator : public RobustIterator<T> {
public:
    virtual Component<T>* next() { 
    	return nullptr; 
    }

    virtual bool isDone() {
        return true;
    }

    virtual void notify_remove(Component<T>* item) {
        return;
    }

    virtual Component<T>* get_owner() {
        return nullptr;
    }
};

// ==========================================================================
template<typename Key, typename Value, typename Arg>
inline bool map_contains(const std::map< Key, Value > m, const Arg& value)
{
    return m.find(value) != m.end();
}

// ==========================================================================
// CompositeIterator class
// ==========================================================================
template <typename T> class CompositeIterator : public RobustIterator<T> {
private:
    stack<Component<T>*> st;
    map<Component<T>*, Iterator<T>*> m;

    void push(Component<T>* owner, Iterator<T>* iterator) {
        st.push(owner);
        m.insert(pair<Component<T>*, Iterator<T>*>(owner, iterator));
    }

    Iterator<T>* top() {
        Component<T>* top_owner = st.top();
        typename std::map<Component<T>*, Iterator<T>*>::iterator it = m.find(top_owner);
        return it->second;
    }

    Iterator<T>* pop() {
        Component<T>* pop_owner = st.top();
        st.pop();
        Iterator<T>* iterator = m.at(pop_owner);
        typename std::map<Component<T>*, Iterator<T>*>::iterator it = m.find(pop_owner);
        m.erase(it);

        return iterator;
    }

public:
    CompositeIterator(RobustIterator<T>* iterator) {
        push(iterator->get_owner(), iterator);
        RobustIterator<T>::owner = iterator->get_owner();
    }

    virtual bool isDone() {
        if (st.size() <= 0) {
            RobustIterator<T>::unsubscribe();
            return true;
        }

        Iterator<T>* iterator = top();

        if (iterator->isDone()) {
            pop();
            return isDone();
        }

        return false;
    }

    virtual Component<T>* next() {
        if (isDone()) {
            return nullptr;
        }

        Iterator<T>* iterator = top();
        Component<T>* component = iterator->next();
        if (component->is_composite()) {
                push(component, component->create_iterator());
            return next();
        }

        return component;
    }

    virtual void notify_remove(Component<T>* item) {
        while (map_contains(m, item)) {
            pop();
        }
    }
};

// ==========================================================================
// Data class
// ==========================================================================
template <typename T> class Data : public Component<T> {
public:
    T data;

    Data(T _data = 0) {
        data = _data;
    }

    virtual Iterator<T>* create_iterator() {
        return new NullIterator<T>();
    }

    virtual bool is_composite() {
        return false;
    }

    virtual string to_string() {
        return std::to_string(data);
    }

    virtual ~Data() {}
};

// ==========================================================================
// Node class
// ==========================================================================
template <typename T> class Node {
public:
    T* data;
    Node<T>* prev;
    Node<T>* next;

    Node(T* _data = 0) {
        data = _data;
        prev = nullptr;
        next = nullptr;
    }
};

// ==========================================================================
template <typename T> class ListIterator;

// ==========================================================================
// List class
// ==========================================================================
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
        Node<T>* tmp = new Node<T>(data);
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
            Node<T>* pNode = new Node<T>(data);
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
        while (!iterator->isDone()) {
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
            if (iterator->isDone()) {
                return (T*)iterator->next();
            }
            else {
                return nullptr;
            }
        }
        while (iterator->isDone()) {
            T* current = (T*)iterator->next();
            if (current == data) {
                if (iterator->isDone()) {
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

// ==========================================================================
// ListIterator class
// ==========================================================================
template <typename T> class ListIterator : public Iterator<T> {
public:
    ListIterator(List<T>* _list)
        : list(_list)
        , current(0) { }

    virtual Component<T>* next() {
        current++;
        return (Component<T>*)list->get(current - 1);
    }

    virtual bool isDone() {
        return current != list->count();
    }

private:
     List<T>* list;
     int current;
};

// ==========================================================================
template <typename T> class GroupIterator;

// ==========================================================================
// Group class
// ==========================================================================
template <typename T> class Group : public Component<T> {
private:
    List<Component<T>>* components = new List<Component<T>>();
    vector<RobustIterator<T>*> iterators;

public:
    void add(Component<T>* item) {
        components->add(item);
    }

    void remove(Component<T>* item) {
        for (int i = 0; i < iterators.size(); i++)
            iterators[i]->notify_remove(item);
        components->remove(item);
    }

    List<Component<T>>* get() {
        return components;
    }

    Iterator<T>* create_iterator() {
        RobustIterator<T>* iterator = new GroupIterator<T>(this);
        iterators.push_back(iterator);

        RobustIterator<T>* composite_iterator = new CompositeIterator<T>(iterator);
        iterators.push_back(composite_iterator);

        return composite_iterator;
    }

    virtual bool is_composite() {
        return true;
    }

    virtual string to_string() {
        string str = "";
        Iterator<T>* iterator = create_iterator();
        while (!iterator->isDone()) {
            Component<int>* item = iterator->next();
                str += item->to_string();

            if (!iterator->isDone())
                str += " ";
        }
        return str;
    }

    void unsubscribe(RobustIterator<T>* iterator) {
        typename vector<RobustIterator<T>*>::iterator it = std::find(iterators.begin(), iterators.end(), iterator);
        if (it != iterators.end())
            iterators.erase(it);
    }
};

// ==========================================================================
// GroupIterator class
// ==========================================================================
template <typename T> class GroupIterator : public RobustIterator<T> {
private:
    List<Component<T>>* list;
    Component<T>* current = nullptr;

public:
    GroupIterator(Group<T>* group) {
        list = group->get();
        RobustIterator<T>::owner = group;
    }

    virtual bool isDone() {
        if (list->get_next(current) == nullptr) {
            RobustIterator<T>::unsubscribe();
            return true;
        }
        return false;
    }

    virtual Component<T>* next() {
        if (isDone()) {
            return nullptr;
        }
        Component<T>* next = list->get_next(current);
          current = next;

        return next;
    }

    virtual void notify_remove(Component<T>* item) {
        if (current != item) {
            return;
        }
        current = list->get_prev(current);
    }
};
