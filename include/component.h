#ifndef COMPONENT_H_
#define COMPONENT_H_

using namespace std;

template <typename T> class Iterator;

template <typename T> class Component {
public:
    virtual Iterator<T>* create_iterator() = 0;
    virtual bool is_composite() = 0;
    virtual string to_string() = 0;

    Component() = default;
    virtual ~Component() = default;
};

#endif  // COMPONENT_H_
