#include <iostream>
#include <memory>
#include "Node-Pilha.h"

using namespace std;

    bool isEmpty(){
        if (head == nullptr) return true;
        else return false;
    }

    void push(int d){
      shared_ptr<Node> newNode = make_shared<Node>(d);
        if(isEmpty()){
            newNode->next = head;
            head = newNode;
        }else{
            newNode->next = head;
            head = newNode;
        }
    }

    void pop(){
        head = head->next;
    }

    void imprime(){
        shared_ptr<Node> ptr = head;

        while(ptr != nullptr){
            cout <<ptr->data<<"-";
            ptr=ptr->next;
        }

    }

    void reverseList(){

        shared_ptr<Node> atual = head->next;
        shared_ptr<Node> ant = nullptr;
        shared_ptr<Node> prox;

        while(prox != nullptr){
            prox = atual->next;
            atual->next = ant;
            ant = atual;
            atual = prox;
        }
         head->next = ant;
    }
