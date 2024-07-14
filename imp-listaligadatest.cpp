#include <iostream>
#include <memory>

using namespace std;


class Node{

public:
    int data;
    unique_ptr<Node> next;

    Node(int d):data(d), next(nullptr){};

};


class LinkedList{

public:
    unique_ptr<Node> head;

    LinkedList(): head(nullptr){};

    void inserir(int newNode){
        unique_ptr<Node> ptr = make_unique<Node>(newNode);
        ptr->next = move(head);
        head = move(ptr);
    }

    void imprime(){
        Node* ptr = head.get();
        while(ptr != nullptr){
            cout << ptr->data << "->";
            ptr = ptr->next.get();
        }
        cout <<"NULL";
    }

    void removeN(int n){

    Node* ptr = head.get();

    while(ptr->next && ptr->next->data != n){
            ptr = ptr->next.get();
        }

    ptr->next= move(ptr->next->next);
    }

    void buscaInsere(int x, int y){

        if(head == nullptr){
            cout <<"A lista está vazia" << endl;
        }

        Node* ptr = head.get();

        if(ptr == nullptr || ptr->data == x){
            unique_ptr<Node> newNode = make_unique<Node>(y);// caso a lista tenha só um elemento
            ptr->next = move(newNode);
        }


        while(ptr->next != nullptr && ptr->next->data != x){
            ptr = ptr->next.get();
        }

        unique_ptr<Node> newNode = make_unique<Node>(y);
        newNode->next = move(ptr->next);
        ptr->next= move(newNode);
    }

    void buscaRemove(int x){
        if(head == nullptr){
        cout << "A lista esta vazia" << endl;
        }

        Node* ptr = head.get();
        while(ptr->next->next != nullptr && ptr->next->next->data != x){
            ptr=ptr->next.get();
        }

        ptr->next = move(ptr->next->next);
    }

    void insereOrdenado(int y){

    if (head == nullptr){
        unique_ptr<Node> newNode = make_unique<Node>(y);
        head->next= move(newNode);
    }

    else
    {
       Node* ptr = head.get();
        if(y >= ptr->data){
         unique_ptr<Node> newNode = make_unique<Node>(y);
         ptr->next = move(newNode);
        }
        else
        {
         cout << "Elemento menor, não foi possivel inserir";
        }
    }

    }

};

int main(){

    LinkedList L1;
    L1.inserir(3);
    //L1.inserir(7);
    //L1.inserir(12);
    //L1.buscaInsere(7,54);
    L1.imprime();
    //L1.buscaInsere(54,12);
    //L1.removeN(3);
    cout << endl;
    //L1.imprime();
    //L1.buscaRemove(54);
    cout<<endl;
    L1.insereOrdenado(1);
    L1.imprime();
}
