## Robust Iterator

**Dmitry Vodopyanov**  
*Lobachevsky University, Nizhny Novgorod, Russia*

C++ implementation of robust and composite iterators.  

Iterators allows to iterate with robustness over simple doubly linked list and composite data structures, like nested lists.  
For instance, to iterate over: 

- simple linked list: ```[0, 1, 2, 3, 4, 5]```,
- nested linked list: ```[0, [1, 2], 3, [4], 5]```.

#### Tested on:  

- Windows 10 + Intel(R) C++ Compiler 17.0, 
- Windows 10 + Visual C++ Compiler 14.0,
- macOS 10.12 + Clang Compiler.

#### Requirements:

- [GoogleTest](https://github.com/google/googletest)
