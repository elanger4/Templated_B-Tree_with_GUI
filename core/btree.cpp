#include "btree.h"
#include "node.h"

// The main function that inserts a new key in this B-Tree
template <typename T>
void btree<T>::insert(T k) {
    // If tree is empty
    if (root == NULL) {
        // Allocate memory for root
        root = new node<T>(degree, true);
        root->setKey(0,k);  // Insert key
        root->setCurrentKeys(1);  // Update number of keys in root
    }
    else {  // If tree is not empty
        // If root is full, then tree grows in height
        if (root->getCurrentKeys() == 2*degree-1) {
            // Allocate memory for new root
            node<T> *s = new node<T>(degree, false);
 
            // Make old root as child of new root
            s->setChildren(0, root);
 
            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);
 
            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->getKey(0) < k)
                i++;
            s->getChildren(i)->insertNonFull(k);
 
            // Change root
            root = s;
        }
        else  // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
    }
}

template <typename T>
void btree<T>::remove(T k) {
    if (!root) {
		std::cout << "The tree is empty\n";
        return;
    }
 
    // Call the remove function for root
    root->remove(k);
 
    // If the root node has 0 keys, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if (root->getCurrentKeys()==0) {
        node<T> *tmp = root;
        if (root->getLeaf())
            root = NULL;
        else
            root = root->getChildren(0);
 
        // Free the old root
        delete tmp;
    }
    return;
}
