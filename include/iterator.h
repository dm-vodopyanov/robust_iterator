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

template <typename T>
class Component;

template <typename T>
class Iterator {
public:
    virtual Component<T>* next() = 0;
    virtual bool is_done() = 0;

    Iterator() = default;
    virtual ~Iterator() = default;
};

#endif  // ITERATOR_H_
