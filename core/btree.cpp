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
    // I dont think this will do it.
    // The root will be gone, but all he other nodes will still me in memory
    // I think we might have to do something like cleanBst();
//		btreeClean(root);
//    delete root; //temp
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
void btree<T>::insert(T value) {  // k=value
    node<T> *x = root;
    while (!x->leaf) {
        int i = 0;
        while (value > x->keys[i] && i < x->keys.length())
            i++;
        node<T> *y = x->children[i];
        if (y->keys.length() < degree) //potential off by one
            x = y;
        else {
            //split y and change x to point to one of the two parts of y.
            //If k is smaller than mid key in y, then set x as first part of y.
                //Else second part of y. 
            //When we split y, we move a key from y to its parent x.
        }
    }
    //x is now a leaf. 
    //insert k into x basic

}


template <typename T>
node<T>* btree<T>::search(T value) {

    /*
    if (root == nullptr) {
        return nullptr;
    } else {
        return search(value, root);
    }
    */
}


/*
   template <typename T>
   node<T>* btree<T>::search(T value, node<T> *nd) {
		for (int i = 0; i < nd.keys.size(); i++) {
			if (value === nd.keys[i]) {
				return nd;
			} else if (value < nd.keys[i]) {
				search(value, nd.keys[i]);
				break;
			} else if (val > nd.keys.size()-1) {
				search(nd.children[nd.children.size()-1], value)
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
		for (int i = 0; i < nd.children.size(); i++) {
			if (nd.children[i] != nullptr) {
				inOrder(nd.children[i];
			} else {
				if (i < nd.keys.size()) {
					cout << nd.keys[i];
				}
			}
		}
   }
   */

template <typename T>
void btree<T>::printInOrder(node<T> *nd) {

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

void btree<T>::btreeClean() {
	if (root == nullptr) {
		return;
	}
	btreeClean(root);
	root = nullptr;
}

void btree<T>::btreeClean(node<T> *nd) {
	if (nd == nullptr)
		return;
	for (int i = 0; i < nd.children.size(); i++) {
		btreeClean(nd.children[i];
	}
	 delete nd;
}

*/
