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

#ifndef COMPOSITE_ITERATOR_H_
#define COMPOSITE_ITERATOR_H_

#include <stack>
#include <map>

using namespace std;

template<typename Key, typename Value, typename Arg>
inline bool map_contains(const std::map< Key, Value > m, const Arg& value) {
    return m.find(value) != m.end();
}

template <typename T>
class CompositeIterator : public RobustIterator<T> {
private:
    stack<Component<T>*> st;
    map<Component<T>*, Iterator<T>*> m;

    void push(Component<T>* owner, Iterator<T>* iterator) {
        st.push(owner);
        m.insert(std::make_pair(owner, iterator));
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

    bool is_done() override {
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

    Component<T>* next() override {
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

    void notify_remove(Component<T>* item) override {
        while (map_contains(m, item)) {  // replace with m.contains(item) (C++20) when
            pop();                       // will available in official clang/gcc
        }
    }
};

#endif  // COMPOSITE_ITERATOR_H_
