/*
MIT License

Copyright (c) 2019 Dmitry Vodopyanov

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

#ifndef ROBUST_ITERATOR_H_
#define ROBUST_ITERATOR_H_

template <typename T>
class RobustIterator : public Iterator<T> {
public:
    RobustIterator() = default;
    virtual ~RobustIterator() = default;

    virtual Component<T>* next() = 0;
    virtual bool is_done() = 0;
    virtual void notify_remove(Component<T>* item) = 0;

    void set_owner(Component<T>* owner_) {
        owner = owner_;
    }

    virtual Component<T>* get_owner() {
        return owner;
    }

    virtual void unsubscribe() {
        if (owner->is_composite()) {
            auto group = (Group<T>*)owner;
            group->unsubscribe(this);
        }
    }

private:
    Component<T>* owner = nullptr;
};

#endif  // ROBUST_ITERATOR_H_
