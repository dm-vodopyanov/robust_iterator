#ifndef DATA_H_
#define DATA_H_

template <typename T> class NullIterator;

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

#endif  // DATA_H_
