#ifndef ITERATOR_H_
#define ITERATOR_H_

#include "component.h"
#include "group.h"
#include "data.h"
#include "list.h"
#include "node.h"

#include "composite_iterator.h"
#include "robust_iterator.h"
#include "group_iterator.h"
#include "null_iterator.h"
#include "list_iterator.h"

template <typename T> class Component;

template <typename T> class Iterator {
public:
    virtual Component<T>* next() = 0;
    virtual bool is_done() = 0;

    Iterator() = default;
    virtual ~Iterator() = default;
};

#endif  // ITERATOR_H_
