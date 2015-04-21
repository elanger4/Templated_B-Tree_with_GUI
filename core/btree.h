#ifndef BTREE_H_
#define BTREE_H_

#include <iostream>
#include "node.h"

template <class T>
class btree {
    public:
        btree();
        ~btree();
        void insert(T value);
        node<T>* search(T value);

    private:
        node<T> *root;
        int degree;
};

#endif
