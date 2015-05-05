#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
template <typename T>
class node {
    public:
        node(){};
        ~node(){};
        int leafInsert(T value) {
            int i = 0;
            while (value > keys[i])
                i++;
            keys.insert(i, value);
			return i;
        }
        std::vector< node<T>* > children;
        std::vector< T* > keys;
		node<T> *parent;
        bool leaf;

};

#endif
