#ifndef BTREE_H_
#define BTREE_H_
#include <iostream>
#include <fstream>
#include "bnode.h"

template <typename T>
class btree {
    bnode<T> *root; // Pointer to root bnode
    int degree;  // Minimum degree 

public:
	bnode<T>* getRoot (); 
    // Constructor (Initializes tree as empty)
    btree(int _degree) {
        root = NULL;
        degree = _degree;
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
    // std::vector<int*>* convertToJack();
	
	template <typename U>
	friend std::ostream &operator<<(std::ostream &stream, const btree<U> &t);

	void writeFile();
	void readFile();
	// std::vector<std::string> readFile(std::string fileName); 
};

#include "btree.cpp"
#endif
