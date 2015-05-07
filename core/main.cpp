#include "btree.h"
#include <iostream>

int main() {
    btree<double> b_tree(3);
	b_tree.insert(1);
	b_tree.insert(2);
	b_tree.insert(3);
	b_tree.insert(4);
	b_tree.search(1);

	b_tree.printInOrder();

	std::cout << "main is working\n";
	b_tree.deleteValue(1);

	b_tree.printInOrder();
	

    return 0;
}
