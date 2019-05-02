## Robust Iterator
[![Travis Build Status](https://travis-ci.org/dmitryvodop/robust_iterator.svg?branch=master)](https://travis-ci.org/dmitryvodop/robust_iterator)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/py7q2tmvy7b4kt8e/branch/master?svg=true)](https://ci.appveyor.com/project/dmitryvodop/robust-iterator/branch/master)
[![The MIT License](https://img.shields.io/github/license/mashape/apistatus.svg)](LICENSE)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Fdmitryvodop%2Frobust_iterator.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2Fdmitryvodop%2Frobust_iterator?ref=badge_shield)


**Dmitry Vodopyanov**

C++17 implementation of robust and composite iterators.  

Iterators allows to iterate with robustness over simple doubly linked list and composite data structures, like nested lists.  
For instance, to iterate over: 

- simple linked list: ```[0, 1, 2, 3, 4, 5]```,
- nested linked list: ```[0, [1, 2], 3, [4], 5]```.

#### Requirements

- [GoogleTest](https://github.com/google/googletest)


#### License

[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Fdmitryvodop%2Frobust_iterator.svg?type=large)](https://app.fossa.io/projects/git%2Bgithub.com%2Fdmitryvodop%2Frobust_iterator?ref=badge_large)