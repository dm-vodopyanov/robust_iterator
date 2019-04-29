## Robust Iterator
[![Build Status](https://travis-ci.org/dmitryvodop/robust_iterator.svg?branch=master)](https://travis-ci.org/dmitryvodop/robust_iterator)
[![The MIT License](https://img.shields.io/github/license/mashape/apistatus.svg)](LICENSE)


**Dmitry Vodopyanov**

C++17 implementation of robust and composite iterators.  

Iterators allows to iterate with robustness over simple doubly linked list and composite data structures, like nested lists.  
For instance, to iterate over: 

- simple linked list: ```[0, 1, 2, 3, 4, 5]```,
- nested linked list: ```[0, [1, 2], 3, [4], 5]```.

#### Requirements:

- [GoogleTest](https://github.com/google/googletest)
