#ifndef BTREE_H_
#define BTREE_H_

#include <iostream>
#include "node.h"

template <typename T>
class btree {
    public:
        btree();
        ~btree();
        void insert(T value);
        node<T>* search(T value);

    private:
		void insert(T value, node<T> *nd);
		node<T>* search(T value, node<T> *nd);

        node<T> *root;
        int degree;
};

#endif
