#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>

template <typename T>
class node {
    public:
        node(){
			isLeaf = true;		
			children.push_back(nullptr);
		};
        ~node(){};

        int nodeInsert(T value) {
            unsigned long i = 0;
			 if (keys.size() == 0) {
			 	keys.push_back(value);
				children.push_back(nullptr);
				return 0;
			 } else {
				while (value >= keys[i] && i < keys.size()) {
					i++;
					}
				}
            keys.insert(keys.begin() + i, value);
			return i;
        }
		
        std::vector< node<T>* > children;
        std::vector<T> keys;
		node<T> *parent;
        bool isLeaf;

};

#endif
