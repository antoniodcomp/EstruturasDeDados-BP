#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class Node{
public:

    T data;
    shared_ptr<Node<T>> next;

    Node(const T &d): data(d), next(nullptr){};
};


template<typename T>
class Fila1{
public:
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> tail;

    Fila1(): head(nullptr), tail(nullptr ) {};

    bool isEmpty()
    {
        if(head == nullptr)return true;
        return false;
    }


    void enqueue(const T &d){
        shared_ptr<Node<T>> newNode= make_shared<Node<T>>(d);

        if(isEmpty())
        {
            newNode->next = head;
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

    }

    void imprime()
    {
        shared_ptr<Node<T>> p = head;

        while(p != nullptr)
        {
            cout <<p->data<< "-";
            p=p->next;
        }

    }

    void dequeue(){

        head = head->next;

    }

};


int main()
{

    Fila1<int> f;
    f.enqueue(1);
    f.enqueue(2);
    f.enqueue(8);
    f.enqueue(7);
    f.dequeue();
    f.enqueue(1);
    f.imprime();
    cout<<endl;

return 0;
}
