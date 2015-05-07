#include "btree.h"

template <typename T>
btree<T>::btree(int d) {
    degree = d;
    root = new node<T>();
    root->isLeaf = true;
    //std::cout << root->isLeaf;
}

template<typename T>
btree<T>::~btree() {
	btreeClean(root);
}


template <typename T>
void btree<T>::insert(T value) {
    if (root == nullptr) {
        node<T>* newNode = new node<T>();
        root = newNode;
		std::cout << "helper works?\n";

    } else {
        insert(value, root);
    }
} 

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
	//
			std::cout << "working1\n";
	if (!(nd->isLeaf)) {
		for (unsigned long i = 0; i < nd->keys.size(); i++) {
			std::cout << "working2\n";
			if (value <= nd->keys[i]) {
			std::cout << "working3\n";
				insert(value, nd->children[i]);
				break;
			} else if (value > nd->keys.size()-1) {
			std::cout << "working3\n";
				insert(value, nd->children[nd->children.size()-1]);
				break;
			}
		}
	} else {
			std::cout << "working5\n";
		if (nd->keys.size() == degree) {
			rotate(value, nd);
		} else {
			nd->nodeInsert(value);
		}
	}
}

template <typename T>
void btree<T>::rotate(T value, node<T> *nd) {
//	now we have to rotate
	std::cout << "rotate called\n";
	if (nd->keys.size() ==  degree) {
		//splits the node
		//find the middle of the nd->keys and creates new nodes 
		//for the front and back halves
		unsigned long mid = degree / 2;
		node<T> *frontHalf = new node<T>();
		node<T> *backHalf = new node<T>();

		//sets the parents of the new nodes
		frontHalf->parent = nd;
		backHalf->parent = nd;
		nd->children.push_back(frontHalf);
		nd->children.push_back(backHalf);

		// copies over values in nodes into new nd->keys
		// and clears out those values in that node
		for (unsigned long i =0; i < nd->keys.size(); i++) {
			if (i == mid) {
				continue;
			} else if (i < mid) {
				frontHalf->keys.push_back(nd->keys[i]);	
				frontHalf->children.push_back(nd->children[i]);	
			} else {
				backHalf->keys.push_back(nd->keys[i]);	
				backHalf->children.push_back(nd->children[i]);	
			}
		}
		std::cout << "Running?\n";
		for (unsigned long i =0; i < nd->keys.size(); i++) {
			if (i == mid) {
				continue;
			} else {
				nd->keys.erase(nd->keys.begin() + i);
				nd->children.erase(nd->children.begin() + i);
			}
		}

		// if its not at the root
		nd->isLeaf = false;
		if (nd->parent != nullptr) {
			//gets the position of where we inserted into the new node
			int pos = nd->parent->nodeInsert(value);

			//sets the pointers the parent node
			nd->parent->children[pos] = frontHalf;
			nd->parent->children[pos+1] = backHalf;
			nd->parent->nodeInsert(mid);
			
			delete nd;
		} 


		frontHalf->isLeaf = true;
		for (unsigned long i =0; i < frontHalf->children.size(); i++) {
			if (frontHalf->children[i] != nullptr) {
				frontHalf->isLeaf = false;
			}
		}

		backHalf->isLeaf = true;
		for (unsigned long i =0; i < backHalf->children.size(); i++) {
			if (backHalf->children[i] != nullptr) {
				backHalf->isLeaf = false;
			}
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

	printInOrder(root);
}

template <typename T>
void btree<T>::printInOrder(node<T> *nd) {

	//probably have to fix the bounds on this
	for (unsigned long i = 0; i < nd->keys.size(); i++) {
		if (nd->children[i] != nullptr) {
			printInOrder(nd->children[i]);
		} else {
			if (i < nd->keys.size()) {
				std::cout << nd->keys[i] << " ";
			}
		}
	}
	std::cout << std::endl;
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

