#include <iostream>
#include <memory>
#include <string>

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

    LinkedList():head(nullptr){};

    void inserir(const T &d){
        shared_ptr<Node<T>> newNode = make_shared<Node<T>>(d);
        newNode->next = head;
        head = newNode;
    }

    void insereNoFinal(const T &d){
        shared_ptr<Node<T>> newNode = make_shared<Node<T>>(d);
        if(head == nullptr){
            newNode->next = head;
            head = newNode;
        }
        else{
            shared_ptr<Node<T>> p = head;

            while(p->next != nullptr){
                p = p->next;
            }

            newNode->next = p->next;
            p->next = newNode;
            p = newNode;
        }
    }

    void liberaNode(){

        while(head ->next != nullptr){
            head = head->next;
        }

        head = nullptr;
    }

    void imprime(){
        shared_ptr<Node<T>> ptr = head;

        if(ptr == nullptr){
            cout <<"Lista vazia" <<endl;
        }

        while(ptr != nullptr){
            cout << ptr->data << "->";
            ptr = ptr->next;
        }

        cout <<"NULL";
        cout<< endl;
    }

    void eliminaUltimoNo(){

        shared_ptr<Node<T>> ptr = head;

        while(ptr->next->next != nullptr){
            ptr = ptr->next;
        }

        ptr->next = nullptr;

    }

    void inverteLista(){

        shared_ptr<Node<T>> anterior = nullptr;
        shared_ptr<Node<T>> atual = head;
        shared_ptr<Node<T>> seguinte = nullptr;

        while(atual != nullptr){
            seguinte = atual->next;
            atual->next = anterior;
            anterior = atual;
            atual = seguinte;
        }

        head = anterior;
    }

    void projetoBrunoInserir(const T &d){
        shared_ptr<Node<T>> newNode = make_shared<Node<T>>(d);
        if(head == nullptr){
            newNode->next = head;
            head = newNode;
        }
        else{
            shared_ptr<Node<T>> p = head;

            while(p->next != nullptr){
                p = p->next;
            }

            newNode->next = p->next;
            p->next = newNode;
            p = newNode;
        }
    }

    void projetoBrunoDelete(const T &d){
    shared_ptr<Node<T>> atual = head;
    shared_ptr<Node<T>> anterior = nullptr;

        while(atual!= nullptr && atual->data != d){
            anterior = atual;
            atual = atual->next;
        }

        if (atual == nullptr) cout << "ELEMENTO NÃO ENCONTRADO" <<endl;

        else{
            anterior->next = atual->next;
        }
    }

    void eliminaN(int n){

        shared_ptr<Node<T>> atual = head;
        shared_ptr<Node<T>> anterior = nullptr;
        int cont = 0;

        while(atual != nullptr && cont != n){
            anterior = atual;
            cont++;
            atual = atual->next;
        }

        anterior -> next = atual ->next;
    }

    void somaLista(){

        if (head == nullptr) cout << "LISTA VAZIA" << endl;

        shared_ptr<Node<T>> atual = head;
        int sum = 0;

        while(atual != nullptr){
            sum += atual->data;
            atual = atual->next;
        }

        cout << sum << endl;

    }

    void eleminaSegElemento(){

        if (head == nullptr) cout << "LISTA VAZIA" << endl;

        shared_ptr<Node<T>> atual = head;
        shared_ptr<Node<T>> anterior = nullptr;
        int cont = 0;

        while(cont != 1){
            anterior = atual;
            cont++;
            atual = atual->next;
        }

        anterior->next = atual->next;
    }

    void insereEnesimo(const T &d, int n){

        shared_ptr<Node<T>> newnode = make_shared<Node<T>>(d);
        shared_ptr<Node<T>> atual = head;
        shared_ptr<Node<T>> anterior = nullptr;
        int cont = 0;

        while(atual != nullptr && cont != n){
            anterior = atual;
            cont++;
            atual = atual->next;
        }

        anterior->next = newnode;
        newnode->next = atual;
    }



};



LinkedList<int> concatenaLista(const LinkedList<int> &l1, const LinkedList<int> &l2){
    LinkedList<int> newList; // Create a new list

    // Iterate through l1 and add elements to newList
    shared_ptr<Node<int>> ptr = l1.head;
    while (ptr != nullptr) {
        newList.insereNoFinal(ptr->data);
        ptr = ptr->next;
    }

    // Iterate through l2 and add elements to newList
    ptr = l2.head;
    while (ptr != nullptr) {
        newList.insereNoFinal(ptr->data);
        ptr = ptr->next;
    }

    return newList;
}



int main(){


    LinkedList<int> l;
    LinkedList<int> p;
    LinkedList<int> mergeL;
    l.insereNoFinal(7);
    l.insereNoFinal(9);
    l.insereNoFinal(8);
    p.insereNoFinal(0);
    p.insereNoFinal(1);
    l.imprime();
    l.eleminaSegElemento();
    l.imprime();

    LinkedList<string> poxim;
    poxim.insereNoFinal("carlos");
    poxim.insereNoFinal("joao");
    poxim.insereNoFinal("ivan");
    poxim.imprime();

    mergeL = concatenaLista(l,p);
    mergeL.imprime();
    mergeL.insereEnesimo(10, 1);
    mergeL.insereEnesimo(18, 1);
     mergeL.insereEnesimo(10, 3);
    mergeL.imprime();

    //a. Incluir um elemento no final de uma lista. [FEITO]
    //b. Concatenar duas listas [Feito/REFAZER]
    //c. Liberar todos os nós de uma lista [FEITO]
    //e. Eliminar o último elemento de uma lista.[Feito]
    //f. Eliminar o enésimo elemento de uma lista.[FEITO]
    //m. Retornar a soma dos inteiros numa lista.[FEITO]
    //k. Eliminar cada segundo elemento de uma lista [feito]




return 0;
}

