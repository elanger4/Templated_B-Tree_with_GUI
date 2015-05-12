#include "btree.h"
#include "bnode.h"
#include <sstream>

template <typename T>
bnode<T>* btree<T>::getRoot () {
	return this->root;
}
// The main function that inserts a new key in this B-Tree
template <typename T>
void btree<T>::readFile()
{
	std::ifstream file("input.txt");
	
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		T value;
		ss >> value;

		insert(value);
	}
}
// template <typename T>
// std::vector<std::string> btree<T>::readFile() {

//     std::ifstream fs("input.txt");
//     std::string line;
//     std::vector<std::string> contents;

//     while (std::getline(fs, line))
// 	{
//         contents.push_back(line);
// 	}
//     return contents;
// }

template <typename T>
void btree<T>::writeFile() {
	std::ofstream file("input.txt");
	file << *this;
	// bnode<T> *nd = new bnode<T>();
	// nd = getRoot();
	// // myfile.open ("input.txt");

    // // for (int i = 0; i < nd->getCurrentKeys(); i++) {
        // // if (nd->getLeaf == false) {
            // // nd->getChildren(i)->writeFile();
	// // 	}
	// // 	myfile << nd->getKey(i) << "\n";
    // // }
 
     // // if (nd->getLeaf == false && nd->getChildren(nd->getCurrentKeys()) != nullptr)
         // // nd->getChildren(nd->getCurrentKeys())->writeFile();

	// //   myfile.close();
}

template <typename T>
void btree<T>::insert(T k) {
    // If tree is empty
    if (root == NULL) {
        // Allocate memory for root
        root = new bnode<T>(degree, true);
        root->setKey(0,k);  // Insert key
        root->setCurrentKeys(1);  // Update number of keys in root
    }
    else {  // If tree is not empty
        // If root is full, then tree grows in height
        if (root->getCurrentKeys() == 2*degree-1) {
            // Allocate memory for new root
            bnode<T> *s = new bnode<T>(degree, false);
 
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
 
    // If the root bnode has 0 keys, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if (root->getCurrentKeys()==0) {
        bnode<T> *tmp = root;
        if (root->getLeaf())
            root = NULL;
        else
            root = root->getChildren(0);
 
        // Free the old root
        delete tmp;
    }
    return;
}

// template <typename T>
// std::vector<int*>* btree<T>::convertToJack() {
//     std::vector<int*> *temp = new std::vector<int*>();
//     temp = root->jackTraverse(temp);
//     return temp;
// }

template <typename U>
std::ostream &operator<<(std::ostream &stream, const btree<U> &tree) {
	if (tree.root) {
		tree.root->traverse(stream);
	}

	return stream;
}
