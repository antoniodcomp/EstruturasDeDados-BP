#ifndef NODE-PILHA_H_INCLUDED
#define NODE-PILHA_H_INCLUDED


#include <memory>

using namespace std;

class Node{

public:
    int data;
    shared_ptr<Node> next;

    Node(int d): data(d), next(nullptr){};
};

class Pilha{

public:
    shared_ptr<Node> head;

    Pilha(): head(nullptr){};


    bool isEmpty();
    void push(int d);
    void pop();
    void imprime();
    void reverseList();

};



#endif // NODE-PILHA_H_INCLUDED
