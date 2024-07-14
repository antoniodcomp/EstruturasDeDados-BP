#include <iostream>
#include <memory>

using namespace std;

class Node{

public:
    int data;
    shared_ptr<Node> next;

    Node(int d):data(d), next(nullptr){};

};

class ListCircular{

public:
    shared_ptr<Node> tail;

    ListCircular(): tail(nullptr){};

    void isTransversal(){

        if(tail == nullptr){
         cout << "Lista Circular esta vazia" <<endl;
        }

        shared_ptr<Node> ptr = tail->next; //
        do{
            cout << ptr->data << "->";
            ptr = ptr->next;
        }while(ptr != tail->next);
        cout <<ptr->next;
    }


    void insere(int d) {
        shared_ptr<Node> newNode = make_shared<Node>(d);
        if (tail == nullptr) {
            tail = newNode;
            tail->next = tail; // Faz o novo nó apontar para ele mesmo
        } else {
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void reverseList(){

        shared_ptr<Node> temp;
        shared_ptr<Node> ptr = tail->next;
        shared_ptr<Node> circular;

        while(ptr->next != tail){
            ptr = ptr->next;
        }

        circular = tail;
        temp = tail->next;
        tail->next = tail->next->next;
        ptr->next = temp;
        tail = temp;
        tail->next = circular;

        shared_ptr<Node> newTemp;
        shared_ptr<Node> x;
        shared_ptr<Node> y;
        shared_ptr<Node> p = tail->next;

        while(p->next != tail){
            newTemp = p->next->next->next;
            x = p->next->next;
            y = p->next;
            p->next->next = newTemp;
            p->next->next->next = y;
            p->next = x;
            p = p->next->next->next;
        }

    }

};

int main(){

    ListCircular L1;

    L1.insere(7);
    L1.insere(8);
    L1.insere(9);
    L1.insere(3);
    L1.isTransversal();
    L1.reverseList();
    cout <<endl;
    L1.isTransversal();

return 0;
}
