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
