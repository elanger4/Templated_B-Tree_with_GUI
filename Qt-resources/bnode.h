#ifndef bnode_H_
#define bnode_H_

#include <iostream>
#include <vector>
#include <string>

#define nullptr 0

template <typename T>
class bnode {

    public:

        int *keys;  // An array of keys
        int degree;      //  Minimum degree (defines the range for number of keys)
        bnode **children; // An array of child pointers
        int currentKeys;     //  Current number of keys
        bool leaf; // Is true when bnode is leaf. Otherwise false

        std::string getTooltip();

        void setKey(int pos, T k) {
            this->keys[pos] = k;
        };

		T getKey(int pos) {
			return this->keys[pos];
		}

		void setChildren(int pos, bnode<T> *nd) {
			this->children[pos] = nd;		
		};

		bnode<T>* getChildren(int pos) {
			return this->children[pos];
		}

		void setCurrentKeys(int num) {
			this->currentKeys = num;
		};

		int getCurrentKeys() {
			return this->currentKeys;
		};
		
		bool getLeaf() {
			return this->leaf;
		}

		bnode<T> (int degree1, bool leaf1);   // Constructor
	 
		// A function to traverse all bnodes in a subtree rooted with this bnode
		void traverse();
        //A similar function to traverse for Jack
        std::vector<int* >* jackTraverse(std::vector<int*>*);
	 
		// A function to search a key in subtree rooted with this bnode.
		bnode<T> *search(T k);   // returns NULL if k is not present.
	 
		// A function that returns the index of the first key that is greater
		// or equal to k
		int findKey(T k);
	 
		// A utility function to insert a new key in the subtree rooted with
		// this bnode. The assumption is, the bnode must be non-full when this
		// function is called
		void insertNonFull(T k);
	 
		// A utility function to split the child y of this bnode. i is index
		// of y in child array children[].  The Child y must be full when this
		// function is called
		void splitChild(int i, bnode *y);
	 
		// A wrapper function to remove the key k in subtree rooted with
		// this bnode.
		void remove(T k);
	 
		// A function to remove the key present in idx-th position in
		// this bnode which is a leaf
		void removeFromLeaf(int idx);
	 
		// A function to remove the key present in idx-th position in
		// this bnode which is a non-leaf bnode
		void removeFromNonLeaf(int idx);
	 
		// A function to get the predecessor of the key- where the key
		// is present in the idx-th position in the bnode
		int getPred(int idx);
	 
		// A function to get the successor of the key- where the key
		// is present in the idx-th position in the bnode
		int getSucc(int idx);
	 
		// A function to fill up the child bnode present in the idx-th
		// position in the children[] array if that child has less than degree-1 keys
		void fill(int idx);
	 
		// A function to borrow a key from the children[idx-1]-th bnode and place
		// it in children[idx]th bnode
		void borrowFromPrev(int idx);
	 
		// A function to borrow a key from the children[idx+1]-th bnode and place it
		// in children[idx]th bnode
		void borrowFromNext(int idx);
	 
		// A function to merge idx-th child of the bnode with (idx+1)th child of
		// the bnode
		void merge(int idx);
	 
		// Make BTree friend of this so that we can access private members of
		// this class in btree functions
};

#include "bnode.cpp"
#endif
