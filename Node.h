#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <memory>

using namespace std;

class Node{

public:
    int data;
    unique_ptr<Node> next;

    Node(int d): data(d), next(nullptr){};
};


#endif // NODE_H_INCLUDED
