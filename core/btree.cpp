#include "btree.h"

template <typename T>
btree<T>::btree(int d) {
    degree = d;
    root = new node<T>();
    root->leaf = true;
    std::cout << root->leaf;
}

template<typename T>
btree<T>::~btree() {
	btreeClean(root);
}

/*
template <typename T>
void btree<T>::insert(T value) {
    if (root == nullptr) {
        node<T>* newNode = new node<T>(value);
        root = newNode;
    } else {
        insert(value, root);
    }
} */

template <typename T>
void btree<T>::insert(T value, node<T> *nd) {  // k=value

    // node<T> *x = root;
    // while (!x->leaf) {
        // int i = 0;
        // while (value > x->keys[i] && i < x->keys.length())
            // i++;
        // node<T> *y = x->children[i];
        // if (y->keys.length() < degree) //potential off by one
            // x = y;
        // else {
            // //split y and change x to point to one of the two parts of y.
            // //If k is smaller than mid key in y, then set x as first part of y.
                // //Else second part of y. 
            // //When we split y, we move a key from y to its parent x.
        // }
    //}
    //x is now a leaf. 
    //insert k into x basic
	if (!(nd->leaf)) {
		for (unsigned long i = 0; i < nd->keys.size(); i++) {
			if (value <= nd->keys[i]) {
				insert(value, nd->keys[i]);
				break;
			} else if (value > nd->keys.size()-1) {
				insert(value, nd->children[nd->children.size()-1]);
				break;
			}
		}
	} else {
		nd->leafInsert(value, nd);
	}
}

template <typename T>
void btree<T>::rotate(T value, node<T> *nd) {
//	now we have to rotate
	if (nd->keys.size() ==  degree) {
		//splits the node
		//find the middle of the nd->keys and creates new nodes 
		//for the front and back halves
		int mid = degree / 2;
		node<T> *frontHalf = new node<T>();
		node<T> *backHalf = new node<T>();

		//sets the parents of the new nodes
		frontHalf->parent = nd;
		backHalf->parent = nd;

		// copies over values in nodes into new nd->keys
		// and clears out those values in that node
		for (int i =0; i < nd->keys.size(); i++) {
			if (i == mid) {
				continue;
			} else if (i < mid) {
				frontHalf->keys.pushBack(nd->keys[i]);	
				nd->keys.erase(i);
			} else {
				backHalf->keys.pushBack(nd->keys[i]);	
				nd->keys.erase(i);
			}
		}

		// if its not at the root
		if (nd->parent != nullptr) {
			//gets the position of where we inserted into the new node
			int pos = nd->parent->keys->leafInsert(value);

			//sets the pointers the parent node
			nd->parent->children[pos] = frontHalf;
			nd->parent->children[pos+1] = backHalf;

			rotate(nd->parent);
			//do i need to delete it after Ive copied it?
			//delete nd;

		} 
	}
}

	
//}


template <typename T>
node<T>* btree<T>::search(T value) {

    if (root == nullptr) {
        return nullptr;
    } else {
        return search(value, root);
    }
}



template <typename T>
node<T>* btree<T>::search(T value, node<T> *nd) {
	for (unsigned long i = 0; i < nd->keys.size(); i++) {
		if (value == nd->keys[i]) {
			return nd;
		} else if (value < nd->keys[i]) {
			search(value, nd->keys[i]);
			break;
		} else if (value > nd->keys.size()-1) {
			search(nd->children[nd->children.size()-1], value);
			break;
		}
	}
}


template <typename T>
void btree<T>::printInOrder() {
	if (root == nullptr)
		return;

	inOrder(root);
}

template <typename T>
void btree<T>::printInOrder(node<T> *nd) {
	for (unsigned long i = 0; i < nd->children.size(); i++) {
		if (nd->children[i] != nullptr) {
			inOrder(nd->children[i]);
		} else {
			if (i < nd->keys.size()) {
				std::cout << nd->keys[i];
			}
		}
	}
}

template <typename T>
std::vector<std::string> btree<T>::readFile() {
    std::ifstream fs("input.txt");
    std::string line;
    std::vector<std::string> contents;
    while (std::getline(fs, line))
        contents.push_back(line);
    return contents;
}

template <typename T>
void btree<T>::writeFile() {
    
}

template <typename T>
void btree<T>::btreeClean() {
	if (root == nullptr) {
		return;
	}
	btreeClean(root);
	root = nullptr;
}

template <typename T>
void btree<T>::btreeClean(node<T> *nd) {
	if (nd == nullptr)
		return;
	for (unsigned long i = 0; i < nd->children.size(); i++) {
		btreeClean(nd->children[i]);
	}
	 delete nd;
}

