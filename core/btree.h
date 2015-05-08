#ifndef BTREE_H_
#define BTREE_H_
#include <iostream>
#include "node.h"

template <typename T>
class btree {
    node<T> *root; // Pointer to root node
    int degree;  // 't' Minimum degree 
public:
 
    // Constructor (Initializes tree as empty)
    btree(int _degree) {
        root = NULL;
        degree = _degree;
    }
 
    void traverse() {
        if (root != NULL) root->traverse();
    }
 
    // function to search a key in this tree
    node<T>* search(T k) {
        return (root == NULL)? NULL : root->search(k);
    }
 
    // The main function that inserts a new key in this B-Tree
    void insert(T k);
 
    // The main function that removes a new key in thie B-Tree
    void remove(T k);
 
};

#include "btree.cpp"
#endif
