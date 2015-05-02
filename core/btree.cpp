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
    delete root; //temp
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

   }

   template <typename T>
   void btree<T>::printInOrder() {
		if (root == nullptr)
			return;

		inOrder(root);
   }

   template <typename T>
   void btree<T>::printInOrder(node<T> *nd) {
		for (int i = 0; i < children.size(); i++) {
			if (children[i] != nullptr) {
				inOrder(children[i];
			} else {
				if (i < keys.size()) {
					cout << keys[i];
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

*/
