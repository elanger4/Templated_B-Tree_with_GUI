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
	// The root will be gone, but all the other nodes will still me in memory
	// I think we might have to do something like cleanBst();
    delete root; //temp
}

template <typename T>
void btree<T>::insert(T value) {
    insert(value, root);
}

/*
template <typename T>
void btree<T>::insert(T value, node<T> *nd) {
    
}

template <typename T>
node<T>* btree<T>::search(T value) {

}

template <typename T>
node<T>* btree<T>::search(T value, node<T> *nd) {

}

template <typename T>
void btree<T>::printInOrder() {

}

template <typename T>
void btree<T>::printInOrder(node<T> *nd) {

}

template <typename T>
void btree<T>::readFile() {

}

template <typename T>
void btree<T>::writeFile() {

}

*/
