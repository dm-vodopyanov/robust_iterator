#ifndef COMPOSITE_ITERATOR_H_
#define COMPOSITE_ITERATOR_H_

#include <stack>
#include <map>

using namespace std;

template<typename Key, typename Value, typename Arg>
inline bool map_contains(const std::map< Key, Value > m, const Arg& value) {
    return m.find(value) != m.end();
}

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
    explicit CompositeIterator(RobustIterator<T>* iterator) {
        push(iterator->get_owner(), iterator);
        RobustIterator<T>::owner = iterator->get_owner();
    }

    virtual bool is_done() {
        if (st.size() <= 0) {
            RobustIterator<T>::unsubscribe();
            return true;
        }

        Iterator<T>* iterator = top();

        if (iterator->is_done()) {
            pop();
            return is_done();
        }

        return false;
    }

    virtual Component<T>* next() {
        if (is_done()) {
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

#endif  // COMPOSITE_ITERATOR_H_
