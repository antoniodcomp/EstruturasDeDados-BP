#include <iostream>
#include  <memory>

using namespace std;

template <typename T>
class Node{

public:
    T data;
    shared_ptr<Node<T>> next;

    Node(const T &d):data(d), next(nullptr){};

};

template <typename T>
class LinkedList{


public:
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> tail;

    LinkedList():head(nullptr), tail(nullptr){};

    bool isEmpty(){return head == nullptr;}

    void add(const T &d){
        shared_ptr<Node<T>> newNode = make_shared<Node<T>>(d);
        if(isEmpty()){
            newNode->next = head;
            head = newNode;
            tail = newNode;
        }
        else if(tail->data == d){
            cout << "ERROR" <<endl;
            return;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        }
    }

    void remover(const T &d){
    shared_ptr<Node<T>> atual = head;
    shared_ptr<Node<T>> anterior = nullptr;

        while(atual!= nullptr && atual->data != d){
            anterior = atual;
            atual = atual->next;
        }

        if (atual == nullptr) cout << "ERROR" <<endl;

        else{
            anterior->next = atual->next;
        }
    }

    bool verificaElem(const T &d){
        shared_ptr<Node<T>> p = head;

        while(p != nullptr){
            if(p->data == d)return true;
            p = p->next;
        }
        return false;

    }
    void show(const T &d){
        //shared_ptr<Node<T>> newNode = make_shared(d);
        shared_ptr<Node<T>> p = head;
        shared_ptr<Node<T>> q = tail;

        if(verificaElem(d)){
            cout << p->data << "<-" << d << "->" <<q->data <<endl;
            return;
        }
        else{
            cout << "?" << "<-" << d << "->" << "?"<<endl;
            return;
        }
    }
};

int main(){

    LinkedList<string> l;

    l.add("jose da silva");
    l.add("jose da silva");
    l.add("joao dos santos");
    l.add("maria da penha");
    l.remover("joao dos santos");
    l.remover("maria da silva");
    l.add("alan turing");
    l.show("jose da silva");
    l.show("maria da penha");
    l.show("bruno prado");

return 0;
}
