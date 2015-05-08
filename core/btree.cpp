#include "btree.h"

template <typename T>
btree<T>::btree(int d) {
    degree = d;
    root = new node<T>();
    root->isLeaf = true;
	root->parent = nullptr;
    //std::cout << root->isLeaf;
}

template<typename T>
btree<T>::~btree() {
	btreeClean(root);
}


template <typename T>
void btree<T>::insert(T value) {
	std::cout << "public inserting: " << value << std::endl;
	insert(value, root);
} 

template <typename T>
void btree<T>::insert(T value, node<T> *nd) {  // k=value

	//the node is not a leaf
	if (!(nd->isLeaf)) {
		for (unsigned long i = 0; i < nd->keys.size(); i++) {
			if (value < nd->keys[0] ) {
				insert(value, nd->children[0]);
				break;
			} else if (value > nd->keys[i] && value < nd->keys[i+1]) {
				insert(value, nd->children[i+1]);
				break;
			} else if (value > nd->keys.size()-1) {
				insert(value, nd->children[nd->children.size()-1]);
				break;
			}
		}
	} else {
		nd->nodeInsert(value);
		if (nd->keys.size() == degree) {
			rotate(value, nd);
		}
	}
}

template <typename T>
void btree<T>::insertRotate(T value, node<T> *nd) {
//	now we have to rotate
	 std::cout << "rotate called\n";
	// //splits the node
	// //find the middle of the nd->keys and creates new nodes 
	// //for the front and back halves
	// node<T> *frontHalf = new node<T>();
	// node<T> *backHalf = new node<T>();

	// //sets the parents of the new nodes
	// frontHalf->parent = nd;
	// backHalf->parent = nd;
	// //have to fix this
	
	// // copies over values in nodes into new nd->keys
	// // and clears out those values in that node
	// unsigned long mid = degree / 2;

	// for (unsigned long i =0; i < nd->keys.size(); i++) {
	// 	std::cout << "copying\n";
	// 	std::cout << "i: " << i << " keys.size(): " << nd->keys.size() << "keys[i]: " << nd->keys[i] <<" mid: " << mid << std::endl;
	// 	if (i == mid) {
	// 		continue;
	// 	} else if (i < mid) {
	// 		frontHalf->keys.push_back(nd->keys[i]);	
	// 	//	frontHalf->children.push_back(nd->children[i]);	
	// 	//	backHalf->children.push_back(nd->children[i]);	
	// 	} else {
	// 		backHalf->keys.push_back(nd->keys[i]);	
	// 		std::cout << "pushed it back nigga" << std::endl;
	// 	}
	// }
	// for (unsigned long i =0; i < nd->keys.size()+1; i++) {
	// 	std::cout << "erasing\n";
	// 	std::cout << "i: " << i << " keys.size(): " << nd->keys.size() << " mid: " << mid << std::endl;
	// 	if (i == mid) {
	// 		continue;
	// 	} else if (i < mid) {
// //			mid--;
	// 		std::cout << "popping: " << nd->keys.front() << std::endl;
	// 		 nd->keys.erase(nd->keys.begin());
	// 		 nd->children.erase(nd->children.begin());
	// 		// nd->keys.pop_front();
	// 		// nd->children.pop_front();
	// 	} else {
	// 		std::cout << "popping: " << nd->keys.back() << std::endl;
	// 		// nd->keys.pop_back();
	// 		nd->children.pop_back();
	// 	}
	// 		//nd->keys.pop_back();
	// }

	// // if its not at the root
	// nd->isLeaf = false;
	// if (nd->parent != nullptr) {
	// 	//gets the position of where we inserted into the new node
	// 	int pos = nd->parent->nodeInsert(value);

	// 	//sets the pointers the parent node
	// 	nd->parent->children[pos] = frontHalf;
	// 	nd->parent->children[pos+1] = backHalf;
	// //	nd->parent->nodeInsert(mid);
	// 	delete nd;
		
	// } else {
	// 	nd->children.erase(nd->children.begin(), nd->children.end());
	// 	nd->children.push_back(frontHalf);
	// 	nd->children.push_back(backHalf);
	// }

	// frontHalf->isLeaf = true;
	// for (unsigned long i =0; i < frontHalf->children.size(); i++) {
	// 	if (frontHalf->children[i] != nullptr) {
	// 		frontHalf->isLeaf = false;
	// 	}
	// }

	// backHalf->isLeaf = true;
	// for (unsigned long i =0; i < backHalf->children.size(); i++) {
	// 	if (backHalf->children[i] != nullptr) {
	// 		backHalf->isLeaf = false;
	// 	}
	// }
	node<T> *frontNode = new node<T>();
	node<T> *backNode = new node<T>();

	frontNode->parent = nd;
	backNode->parent = nd;
	
	unsigned long mid = degree / 2;
	std::cout << "mid: " << mid << std::endl;

	for(unsigned long i =0; i < mid; i++) {
		std::cout << "inserting: " << nd->keys[i] << std::endl;
		frontNode->keys.push_back(nd->keys[i]);
		frontNode->children.push_back(nd->children[i]);
		std::cout << "popping: " << nd->keys[i] << std::endl;
		nd->keys.erase(nd->keys.begin());
	}

	for(unsigned long i = mid+1; i < nd->keys.size(); i++) {
		std::cout << "inserting: " << nd->keys[i] << std::endl;
		backNode->keys.push_back(nd->keys[i]);
		backNode->children.push_back(nd->children[i]);
		std::cout << "popping: " << nd->keys[i] << std::endl;
		nd->keys.pop_back();
	}

	if (!(nd->isLeaf)) {
		int pos = nd->parent->nodeInsert(value);	
	 	nd->parent->children.insert(nd->parent->children.begin()+pos, frontNode);
	 	nd->parent->children.insert(nd->parent->children.begin()+pos+1, backNode);
	} else {
		nd->children.push_back(frontNode);
		nd->children.push_back(backNode);
	}

	if (nd != root) {
		rotate(nd->parent);
	}
}

void btree<T>::rotate(node<T>* nd) {
	if (nd->keys.size() == degree) {

	}
}

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
	std::cout << "nd->keysn .size(): " << nd->keys.size() << "\n";
	for (unsigned long i = 0; i < nd->keys.size(); i++) {
		if (value == nd->keys[i]) {
			return nd;
		} 
	}
	std::cout << "working2\n";
	node<T> *retNode = new node<T>();
	retNode = nullptr;
	std::cout << "working3\n";
		
	for (unsigned long i = 0; i < nd->keys.size(); i++) {
		std::cout << "keys[0]: " << nd->keys[0] << "\n";
		if (value < nd->keys[0]) {
			std::cout << "this1";
			retNode = search(value, nd->children[0]);
			break;
		} else if (value > nd->keys[i] && value < nd->keys[i+1]) {
			std::cout << "this2";
			retNode = search(value, nd->children[i+1]);
			break;
		} else if (value > nd->keys.size()-1) {
			std::cout << "this3";
			retNode = search(value, nd->children[nd->children.size()-1]);
			break;
		}
		std::cout << "end for loop\n";
	}
	std::cout << "working4\n";
	return retNode;
}

template <typename T>
void btree<T>::deleteValue(T value) {
	node<T> *deleteNode = search(value);
	if (deleteNode->isLeaf) {
		for (unsigned long i =0; i < deleteNode->keys.size(); i++) {
			if (value == deleteNode->keys[i]) {
				deleteNode->keys.erase(deleteNode->keys.begin()+i);
			}
		}
	} else {

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
//	std::cout << "values in each node: ";
	for (unsigned long i = 0; i < nd->keys.size(); i++) {
//		std::cout << "value " << i << ": " << nd->keys[i] << ", ";
	}
	std::cout << std::endl;
	for (unsigned long i = 0; i < nd->keys.size(); i++) {

		if (nd->children[i] != nullptr) {
//			std::cout << "recursing\n";
			printInOrder(nd->children[i]);
//			std::cout << "still recursing\n";
			std::cout << nd->keys[i] << ", ";
		} else {
				std::cout << nd->keys[i] << ", ";

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

