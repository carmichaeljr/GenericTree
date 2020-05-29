# GenericTree
A generic tree implementation in C++ based on the STL containers that allows for arbitray numbers of elements to exist at each level in the tree.

### Interface
The ```Tree``` classes interface was inspired by the STL containers, and contains many methods of the same name, parameter type, and return type as the STL containers. For example:
```
int size(void)
bool empty(void)
Tree<T>::iterator begin()
Tree<T>::iterator end()
void emplace(const Tree<T>::iterator &sibling, const T &data)
Tree<T>::iterator find(const T &data)
Tree<T>::iterator erase(const Tree<T>::iterator &start)
void clear(void)
```

### Iteration
This container was designed to make iteration cheap and efficient. The internal structure is a set of linked nodes, which allows the iterator to just contain a pointer to the current node. This implementaion avoids wasting memory by creating a stack of elements to visit in the future, which becomes more costly the larger the tree and only compounds with more iterators.

### Internal Structure
The basic building block of a generic tree is a ```Node```. ```Node```'s are allocated on the heap and contain the data of the container as well as pointers to the next, parent, and first child ```Node```. Only the last child in a list of siblings has the pointer to the parent ```Node```, as shown below.
```
            ---------------(Parent Node) <------------------
            |                                              |
           \/                                              |
    (Child Node 1) ---> (Child Node 2) -> ... ---> (Last Child Node)
```

### Use
This class requires C++11 or greater. There are no dependencies outside of the files listed in the repository. To use the class just place the repositories files in the same directory as the rest of your source files, and include the ```Tree.hpp``` file in your code as needed.
