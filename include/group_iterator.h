/*
 * MIT License
 *
 * Copyright (c) 2018 Dmitry Vodopyanov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef GROUP_ITERATOR_H_
#define GROUP_ITERATOR_H_

template <typename T> class GroupIterator : public RobustIterator<T> {
private:
    List<Component<T>>* list;
    Component<T>* current = nullptr;

public:
    explicit GroupIterator(Group<T>* group) {
        list = group->get();
        RobustIterator<T>::owner = group;
    }

    virtual bool is_done() {
        if (list->get_next(current) == nullptr) {
            RobustIterator<T>::unsubscribe();
            return true;
        }
        return false;
    }

    virtual Component<T>* next() {
        if (is_done()) {
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

#endif  // GROUP_ITERATOR_H_
