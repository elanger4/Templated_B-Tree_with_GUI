#ifndef BTREE_H_
#define BTREE_H_

#include <iostream>
#include "node.h"
#include <fstream>

template <typename T>
class btree {
    public:
        btree(int d);
        ~btree();
        void insert(T value);
        node<T>* search(T value);
        void printInOrder();
        std::vector<std::string> readFile();
        void writeFile();

    private:
        void insert(T value, node<T> *nd);
        node<T>* search(T value, node<T> *nd);
        void printInOrder(node<T> *nd);

        node<T> *root;
        int degree;
};

#include "btree.cpp"

#endif
