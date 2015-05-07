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
	std::cout << "inserting: " << value << std::endl;
    if (root == nullptr) {
        node<T>* newNode = new node<T>();
        root = newNode;

    } else {
        insert(value, root);
    }
} 

template <typename T>
void btree<T>::insert(T value, node<T> *nd) {  // k=value

	std::cout << "working1\n";
	//the node is not a leaf
	std::cout << "isLeaf: " << nd->isLeaf << std::endl;
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
			nd->nodeInsert(value);
		if (nd->keys.size() == degree) {
			rotate(value, nd);
		}
	}
}

template <typename T>
void btree<T>::rotate(T value, node<T> *nd) {
//	now we have to rotate
	std::cout << "rotate called\n";
	//splits the node
	//find the middle of the nd->keys and creates new nodes 
	//for the front and back halves
	unsigned long mid = degree / 2;
	node<T> *frontHalf = new node<T>();
	node<T> *backHalf = new node<T>();

	//sets the parents of the new nodes
	frontHalf->children.push_back(nullptr);
	backHalf->children.push_back(nullptr);

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
		//	frontHalf->children.push_back(nd->children[i]);	
		//	backHalf->children.push_back(nd->children[i]);	
		} else {
			backHalf->keys.push_back(nd->keys[i]);	
		}
	}
	std::cout << "Running?\n";
	for (unsigned long i =0; i < nd->keys.size(); i++) {
		if (i == mid) {
			continue;
		} else if (i < mid) {
			nd->keys.erase(nd->keys.begin() + i);
			nd->children.erase(nd->children.begin() + i);
		} else {
			nd->keys.erase(nd->keys.begin() + 1);
			nd->children.erase(nd->children.begin() + 1);
		}
	}

	std::cout << "Running1?\n";
	// if its not at the root
	nd->isLeaf = false;
	if (nd->parent != nullptr) {
		//gets the position of where we inserted into the new node
		int pos = nd->parent->nodeInsert(value);

		//sets the pointers the parent node
		nd->parent->children[pos] = frontHalf;
		nd->parent->children[pos+1] = backHalf;
	//	nd->parent->nodeInsert(mid);
		
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
		} 
	}
		
	for (unsigned long i = 0; i < nd->keys.size(); i++) {
		if (value > nd->keys[i] && value < nd->keys[i+1]) {
			search(value, nd->children[i+1]);
		} else if (value > nd->keys.size()-1) {
			search(value, nd->children[nd->children.size()-1]);
			break;
		}
	}
	return nullptr;
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
			std::cout << nd->keys[i] << " ";
		} else {
				std::cout << nd->keys[i] << " ";
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

