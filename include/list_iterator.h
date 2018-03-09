#ifndef LIST_ITERATOR_H_
#define LIST_ITERATOR_H_

template <typename T> class ListIterator : public Iterator<T> {
public:
    explicit ListIterator(List<T>* _list)
            : list(_list)
            , current(0) { }

    virtual Component<T>* next() {
        current++;
        return (Component<T>*)list->get(current - 1);
    }

    virtual bool is_done() {
        return current != list->count();
    }

private:
    List<T>* list;
    int current;
};

#endif  // LIST_ITERATOR_H_
