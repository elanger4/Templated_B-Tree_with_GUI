#ifndef BTREE_H_
#define BTREE_H_
#include <iostream>
#include "bnode.h"

template <typename T>
class btree {
    bnode<T> *root; // Pointer to root bnode
    int degree;  // Minimum degree 
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
    bnode<T>* search(T k) {
        return (root == NULL)? NULL : root->search(k);
    }
 
    // The main function that inserts a new key in this btree
    void insert(T k);
 
    // The main function that removes a new key in thie btree
    void remove(T k);

    //Jack's function to give his std::vector
    std::vector<int*>* convertToJack();
 
};

#include "btree.cpp"
#endif
