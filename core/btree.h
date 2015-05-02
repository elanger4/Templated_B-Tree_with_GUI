#ifndef BTREE_H_
#define BTREE_H_

#include <iostream>
#include "node.h"

template <typename T>
class btree {
    public:
        btree(int d);
        ~btree();
        void insert(T value);
        node<T>* search(T value);
        void printInOrder();
        void readFile();
        void writeFile();

    private:
        void insert(T value, node<T> *nd);
        node<T>* search(T value, node<T> *nd);
        void printInOrder(node<T> *nd);

        node<T> *root;
        unsigned int degree;
};

#include "btree.cpp"

#endif
