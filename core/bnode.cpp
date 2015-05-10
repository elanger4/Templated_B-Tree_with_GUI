#include "bnode.h"

template <typename T>
bnode<T>::bnode(int degree1, bool leaf1) {
    // Copy the given minimum degree and leaf property
    degree = degree1;
    leaf = leaf1;
 
    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new int[2*degree-1];
    children = new bnode *[2*degree];
 
    // Initialize the number of keys as 0
    currentKeys = 0;
}
 
// A utility function that returns the index of the first key that is
// greater than or equal to k
template <typename T>
int bnode<T>::findKey(T k) {
    int idx=0;
    while (idx<currentKeys && keys[idx] < k)
        ++idx;
    return idx;
}
 
// A function to remove the key k from the sub-tree rooted with this bnode
template <typename T>
void bnode<T>::remove(T k) {
    int idx = findKey(k);
 
    // The key to be removed is present in this bnode
    if (idx < currentKeys && keys[idx] == k) {
 
        // If the bnode is a leaf bnode - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else {
        // If this bnode is a leaf bnode, then the key is not present in tree
        if (leaf) {
			std::cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }
 
        // The key to be removed is present in the sub-tree rooted with this bnode
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this bnode
        bool flag = ( (idx==currentKeys)? true : false );
 
        // If the child where the key is supposed to exist has less that degree keys,
        // we fill that child
        if (children[idx]->currentKeys < degree)
            fill(idx);
 
        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast degree keys
        if (flag && idx > currentKeys)
            children[idx-1]->remove(k);
        else
            children[idx]->remove(k);
    }
    return;
}
 
// A function to remove the idx-th key from this bnode - which is a leaf bnode
template <typename T>
void bnode<T>::removeFromLeaf (int idx) {
 
    // Move all the keys after the idx-th pos one place backward
    for (int i=idx+1; i < currentKeys; ++i)
        keys[i-1] = keys[i];
 
    // Reduce the count of keys
    currentKeys--;
 
    return;
}
 
// A function to remove the idx-th key from this bnode - which is a non-leaf bnode
template <typename T>
void bnode<T>::removeFromNonLeaf(int idx) {
 
    int k = keys[idx];
 
    // If the child that precedes k (children[idx]) has atleast degree keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // children[idx]. Replace k by pred. Recursively delete pred
    // in children[idx]
    if (children[idx]->currentKeys >= degree) {
        int pred = getPred(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    }
 
    // If the child children[idx] has less that degree keys, examine children[idx+1].
    // If children[idx+1] has atleast degree keys, find the successor 'succ' of k in
    // the subtree rooted at children[idx+1]
    // Replace k by succ
    // Recursively delete succ in children[idx+1]
    else if  (children[idx+1]->currentKeys >= degree) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        children[idx+1]->remove(succ);
    }
 
    // If both children[idx] and children[idx+1] has less that degree keys,merge k and all of children[idx+1]
    // into children[idx]
    // Now children[idx] contains 2*degree-1 keys
    // Free children[idx+1] and recursively delete k from children[idx]
    else {
        merge(idx);
        children[idx]->remove(k);
    }
    return;
}
 
// A function to get predecessor of keys[idx]
template <typename T>
int bnode<T>::getPred(int idx) {
    // Keep moving to the right most bnode until we reach a leaf
    bnode<T> *cur=children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->currentKeys];
 
    // Return the last key of the leaf
    return cur->keys[cur->currentKeys-1];
}
 
template <typename T>
int bnode<T>::getSucc(int idx) {
 
    // Keep moving the left most bnode starting from children[idx+1] until we reach a leaf
    bnode<T> *cur = children[idx+1];
    while (!cur->leaf)
        cur = cur->children[0];
 
    // Return the first key of the leaf
    return cur->keys[0];
}
 
// A function to fill child children[idx] which has less than degree-1 keys
template <typename T>
void bnode<T>::fill(int idx) {
 
    // If the previous child(children[idx-1]) has more than degree-1 keys, borrow a key
    // from that child
    if (idx!=0 && children[idx-1]->currentKeys>=degree)
        borrowFromPrev(idx);
 
    // If the next child(children[idx+1]) has more than degree-1 keys, borrow a key
    // from that child
    else if (idx!=currentKeys && children[idx+1]->currentKeys>=degree)
        borrowFromNext(idx);
 
    // Merge children[idx] with its sibling
    // If children[idx] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else {
        if (idx != currentKeys)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}
 
// A function to borrow a key from children[idx-1] and insert it
// into children[idx]
template <typename T>
void bnode<T>::borrowFromPrev(int idx) {
 
    bnode<T> *child=children[idx];
    bnode<T> *sibling=children[idx-1];
 
    // The last key from children[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in children[idx]. Thus, the  loses
    // sibling one key and child gains one key
 
    // Moving all key in children[idx] one step ahead
    for (int i=child->currentKeys-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];
 
    // If children[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->leaf) {
        for(int i=child->currentKeys; i>=0; --i)
            child->children[i+1] = child->children[i];
    }
 
    // Setting child's first key equal to keys[idx-1] from the current bnode
    child->keys[0] = keys[idx-1];
 
    // Moving sibling's last child as children[idx]'s first child
    if (!leaf)
        child->children[0] = sibling->children[sibling->currentKeys];
 
    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    keys[idx-1] = sibling->keys[sibling->currentKeys-1];
 
    child->currentKeys += 1;
    sibling->currentKeys -= 1;
 
    return;
}
 
// A function to borrow a key from the children[idx+1] and place
// it in children[idx]
template <typename T>
void bnode<T>::borrowFromNext(int idx) {
 
    bnode<T> *child=children[idx];
    bnode<T> *sibling=children[idx+1];
 
    // keys[idx] is inserted as the last key in children[idx]
    child->keys[(child->currentKeys)] = keys[idx];
 
    // Sibling's first child is inserted as the last child
    // into children[idx]
    if (!(child->leaf))
        child->children[(child->currentKeys)+1] = sibling->children[0];
 
    //The first key from sibling is inserted into keys[idx]
    keys[idx] = sibling->keys[0];
 
    // Moving all keys in sibling one step behind
    for (int i=1; i<sibling->currentKeys; ++i)
        sibling->keys[i-1] = sibling->keys[i];
 
    // Moving the child pointers one step behind
    if (!sibling->leaf) {
        for(int i=1; i<=sibling->currentKeys; ++i)
            sibling->children[i-1] = sibling->children[i];
    }
 
    // Increasing and decreasing the key count of children[idx] and children[idx+1]
    // respectively
    child->currentKeys += 1;
    sibling->currentKeys -= 1;
 
    return;
}
 
// A function to merge children[idx] with children[idx+1]
// children[idx+1] is freed after merging
template <typename T>
void bnode<T>::merge(int idx) {
    bnode<T> *child = children[idx];
    bnode<T> *sibling = children[idx+1];
 
    // Pulling a key from the current bnode and inserting it into (dehree-1)th
    // position of children[idx]
    child->keys[degree-1] = keys[idx];
 
    // Copying the keys from chidlrenl[idx+1] to children[idx] at the end
    for (int i=0; i<sibling->currentKeys; ++i)
        child->keys[i+degree] = sibling->keys[i];
 
    // Copying the child pointers from children[idx+1] to children[idx]
    if (!child->leaf) {
        for(int i=0; i<=sibling->currentKeys; ++i)
            child->children[i+degree] = sibling->children[i];
    }
 
    // Moving all keys after idx in the current bnode one step before -
    // to fill the gap created by moving keys[idx] to children[idx]
    for (int i=idx+1; i<currentKeys; ++i)
        keys[i-1] = keys[i];
 
    // Moving the child pointers after (idx+1) in the current bnode one
    // step before
    for (int i=idx+2; i<=currentKeys; ++i)
        children[i-1] = children[i];
 
    // Updating the key count of child and the current bnode
    child->currentKeys += sibling->currentKeys+1;
    currentKeys--;
 
    // Freeing the memory occupied by sibling
    delete(sibling);
    return;
}

template <typename T>
void bnode<T>::insertNonFull(T k) {
    // Initialize index as index of rightmost element
    int i = currentKeys-1;
 
    // If this is a leaf bnode
    if (leaf == true) {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i] > k) {
            keys[i+1] = keys[i];
            i--;
        }
 
        // Insert the new key at found location
        keys[i+1] = k;
        currentKeys = currentKeys+1;
    }
    else {  // If this bnode is not leaf
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k)
            i--;
 
        // See if the found child is full
        if (children[i+1]->currentKeys == 2*degree-1) {
            // If the child is full, then split it
            splitChild(i+1, children[i+1]);
 
            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (keys[i+1] < k)
                i++;
        }
        children[i+1]->insertNonFull(k);
    }
}
 
// A utility function to split the child y of this bnode
// Note that y must be full when this function is called
template <typename T>
void bnode<T>::splitChild(int i, bnode<T> *y) {
    // Create a new bnode which is going to store (t-1) keys
    // of y
    bnode<T> *z = new bnode<T>(y->degree, y->leaf);
    z->currentKeys = degree - 1;
 
    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < degree-1; j++)
        z->keys[j] = y->keys[j+degree];
 
    // Copy the last t children of y to z
    if (y->leaf == false) {
        for (int j = 0; j < degree; j++)
            z->children[j] = y->children[j+degree];
    }
 
    // Reduce the number of keys in y
    y->currentKeys = degree - 1;
 
    // Since this bnode is going to have a new child,
    // create space of new child
    for (int j = degree; j >= i+1; j--)
        children[j+1] = children[j];
 
    // Link the new child to this bnode
    children[i+1] = z;
 
    // A key of y will move to this bnode. Find location of
    // new key and move all greater keys one space ahead
    for (int j = currentKeys-1; j >= i; j--)
        keys[j+1] = keys[j];
 
    // Copy the middle key of y to this bnode
    keys[i] = y->keys[degree-1];
 
    // Increment count of keys in this bnode
    currentKeys = currentKeys + 1;
}
 
// Function to traverse all bnodes in a subtree rooted with this bnode
template <typename T>
void bnode<T>::traverse() {
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < currentKeys; i++) {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
//		std::cout << "still working?\n";
        if (leaf == false) {
            children[i]->traverse();
		}
		std::cout << " " << keys[i];
    }
 
	// std::cout << "this runs2\n";
     // Print the subtree rooted with last child
     if (leaf == false && children[currentKeys] != nullptr)
         children[currentKeys]->traverse();
}
 
// Function to search key k in subtree rooted with this bnode
template <typename T>
bnode<T> *bnode<T>::search(T k) {
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < currentKeys && k > keys[i])
        i++;
 
    // If the found key is equal to k, return this bnode
    if (keys[i] == k)
        return this;
 
    // If key is not found here and this is a leaf bnode
    if (leaf == true)
        return nullptr;
 
    // Go to the appropriate child
    return children[i]->search(k);
}
