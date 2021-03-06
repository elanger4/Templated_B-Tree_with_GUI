#include <iostream>

#include "btree.h"

int main() {
    btree<int> t(3); // A B-Tree with minium degree 3
 
    t.insert(1);
    t.insert(3);
    t.insert(7);
    t.insert(10);
    t.insert(11);
    t.insert(13);
    t.insert(14);
    t.insert(15);
    t.insert(18);
    t.insert(16);
    t.insert(19);
    t.insert(24);
    t.insert(25);
    t.insert(26);
    t.insert(21);
    t.insert(4);
    t.insert(5);
    t.insert(20);
    t.insert(22);
    t.insert(2);
    t.insert(17);
    t.insert(12);
    t.insert(6);

	// std::vector<std::string> readTheFile = t.readFile();

	// for (unsigned long i =0; i < readTheFile.size(); i++) {
	// 	std::cout << "element: " << readTheFile[i] << std::endl;
	// } 
	
	t.readFile();

    std::cout << "Traversal of tree constructed is\n" << t << std::endl;

	// std::cout << "root" << t.getRoot()->getKey(0);
 
    // t.remove(6);
    // std::cout << "Traversal of tree after removing 6\n";
    // t.traverse();
    // std::cout << std::endl;
 
    // t.remove(13);
    // std::cout << "Traversal of tree after removing 13\n";
    // t.traverse();
    // std::cout << std::endl;
 
    // t.remove(7);
    // std::cout << "Traversal of tree after removing 7\n";
    // t.traverse();
    // std::cout << std::endl;
 
    // t.remove(4);
    // std::cout << "Traversal of tree after removing 4\n";
    // t.traverse();
    // std::cout << std::endl;
 
    // t.remove(2);
    // std::cout << "Traversal of tree after removing 2\n";
    // t.traverse();
    // std::cout << std::endl;
	
	t.writeFile();
	return 0;
};



