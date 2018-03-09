## Robust Iterator

**Dmitry Vodopyanov**

C++ implementation of robust and composite iterators.  

Iterators allows to iterate with robustness over simple doubly linked list and composite data structures, like nested lists.  
For instance, to iterate over: 

- simple linked list: ```[0, 1, 2, 3, 4, 5]```,
- nested linked list: ```[0, [1, 2], 3, [4], 5]```.

#### Tested on:  

- Ubuntu 16.04 + Intel(R) C++ Compiler 18.0.1,
- Ubuntu 16.04 + GCC 5.4.0,
- macOS 10.12 + Clang Compiler,
- Windows 10 + Intel(R) C++ Compiler 17.0.1,
- Windows 10 + Visual C++ Compiler 14.0.

#### Requirements:

- [GoogleTest](https://github.com/google/googletest)
