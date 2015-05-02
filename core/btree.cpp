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
		btreeClean(root);
//    delete root; //temp
}

template <typename T>
void btree<T>::insert(T value) {
    if (root == nullptr) {
        node<T>* newNode = new node<T>(value);
        root = newNode;
    } else {
        insert(value, root);
    }
}

template <typename T>
void btree<T>::insert(T value, node<T> *nd) { //this signature may be off. not sure how we want to architect inserting

}


template <typename T>
node<T>* btree<T>::search(T value) {
    if (root == nullptr) {
        return nullptr;
    } else {
        return search(value, root);
    }
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

   template <typename T>
   void btree<T>::readFile() {

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
