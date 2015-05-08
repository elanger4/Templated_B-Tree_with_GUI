#include "btree.h"
#include <iostream>

int main() {
    btree<double> b_tree(3);
	b_tree.insert(1);
	b_tree.insert(2);
	b_tree.insert(3);
	//b_tree.insert(4);
	std::cout << "about to search\n";
	b_tree.printInOrder();
	b_tree.search(1);
	std::cout << "searched\n";


    return 0;
}
