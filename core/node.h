#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>

template <typename T>
class node {
    public:
  node(){};
        ~node(){};
        std::vector< node<T>* > children;
        std::vector< T* > keys;
        bool leaf;
        //node<T> *children[];
        //T *keys[];

        //friend class btree;
};

#endif
