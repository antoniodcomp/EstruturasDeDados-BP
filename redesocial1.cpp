#include <iostream>
#include <memory>
#include <string>

using namespace std;

template <typename T>
class Node{

 public:
    T data;
    shared_ptr<Node<T>> next;
    shared_ptr<Node<T>> prev;

    Node(const T& d): data(d), next(nullptr), prev(nullptr){};
};

template <typename T>
class RedeSocial{
 public:
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> tail;

    RedeSocial(): head(nullptr), tail(nullptr){};

    bool isEmpty(){return head == nullptr;}

    void insertion(const T& d){
        shared_ptr<Node<T>> newNode = make_shared<Node<T>>(d);
        if(isEmpty()){
            head = newNode;
            tail = newNode;
            head->next = head;
            head->prev = head;
            tail->next = tail;
            tail->prev = tail;
        }
        else if(tail->data == d){
            cout << "ERROR" <<endl;
            return;
        }
        else{
            newNode->next = tail->next;
            tail->next = newNode;
            newNode->prev = tail;
            head->prev = newNode;
            tail = newNode;
        }
    }

    void remover(const T& d){
    // Verificar se a lista est� vazia
    if(head == nullptr){
        cout << "Lista Circular esta vazia" << endl;
        return; // N�o h� nada para remover
    }

    shared_ptr<Node<T>> atual = head;
    shared_ptr<Node<T>> temp = nullptr;
    shared_ptr<Node<T>> temp2 = nullptr;

    // Encontrar o elemento ou chegar ao final da lista
    while(atual->data != d && atual->next != head){
        atual = atual->next;
    }

    // Verificar se o elemento foi encontrado
    if(atual->data == d){
        // Remover o elemento
        temp = atual->next;
        temp2 = atual->prev;
        temp->prev = temp2;
        temp2->next = temp;

        // Atualizar o ponteiro head se o elemento removido era o primeiro
        if(atual == head){
            head = temp; // Atualiza o head para o pr�ximo elemento
        }
    } else {
        cout << "Elemento nao encontrado" << endl;
    }
}

 void printList(){
    if(head == nullptr){
        cout << "Lista Circular esta vazia" << endl;
    } else {
        shared_ptr<Node<T>> ptr = head;

        do{
            cout << ptr->data << "->";
            ptr = ptr->next;
        } while(ptr != head); // Corrigir condi��o para evitar loop infinito
    }
 }

 shared_ptr<Node<T>> busca(const T& d){
    shared_ptr<Node<T>> ptr = head;

    do{
        if(ptr->data == d)return ptr;
        ptr = ptr->next;
    } while(ptr != head);

    return nullptr;
 }

 void show(const T& d){
    shared_ptr<Node<T>> p = busca(d);

    if(p != nullptr){
        shared_ptr<Node<T>> temp1 = nullptr;
        shared_ptr<Node<T>> temp2 = nullptr;
        temp1 = p->prev;
        temp2 = p->next;

        cout << temp1->data << "<-" << p->data << "->" << temp2->data <<endl;
    }
    else{
        cout << "<?" << d << "?>";
    }
 }

};

int main(){

    RedeSocial<string> L1;

    L1.insertion("jose da silva");
    L1.insertion("jose da silva");
    L1.insertion("joao dos santos");
    L1.insertion("maria da penha");
    L1.remover("joao dos santos");
    L1.remover("maria da silva");
    L1.insertion("alan turing");
    L1.show("maria da penha");
    L1.show("bruno prado");



    return 0;
}
