#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>

template <typename T>
class node {
    public:
        node(){};
        ~node(){};
        void leafInsert(T value) {
            int i = 0;
            while (value > keys[i])
                i++;
            keys.insert(i, value);
        }
        std::vector< node<T>* > children;
        std::vector< T* > keys;
        bool leaf;

};

#endif
