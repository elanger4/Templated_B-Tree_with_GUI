#ifndef NODE_H_
#define NODE_H_

#include <iostream>

template <class T>
class node {
    public:
        node();
        ~node();

    private:
        node<T> *children[];
        T *keys[];
        bool leaf;

//friend class btree;
};

#endif
