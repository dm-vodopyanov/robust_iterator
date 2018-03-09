#ifndef NULL_ITERATOR_H_
#define NULL_ITERATOR_H_

template <typename T> class NullIterator : public RobustIterator<T> {
public:
    virtual Component<T>* next() {
        return nullptr;
    }

    virtual bool is_done() {
        return true;
    }

    virtual void notify_remove(Component<T>* item) {
        return;
    }

    virtual Component<T>* get_owner() {
        return nullptr;
    }
};

#endif  // NULL_ITERATOR_H_
