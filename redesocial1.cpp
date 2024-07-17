#include <iostream>
#include <memory>
#include <string>
#include <fstream>


using namespace std;

//ofstream arquivoS("teste3.txt");


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

    bool add(const T& d){
        shared_ptr<Node<T>> newNode = make_shared<Node<T>>(d);
        if(isEmpty()){
            head = newNode;
            tail = newNode;
            head->next = head;
            head->prev = head;
            tail->next = tail;
            tail->prev = tail;
            return true;
        }
        else if(tail->data == d){
            return false;
        }
        else{
            newNode->next = tail->next;
            tail->next = newNode;
            newNode->prev = tail;
            head->prev = newNode;
            tail = newNode;
            return true;
        }
    }



    bool verificaAdd(const T &d){
        if(tail->data == d){
            return true;
        }
        else return false;
    }



    void remover(const T& d){

    if(isEmpty()){
        cout << "Lista Circular esta vazia" << endl;
        return;
    }

    shared_ptr<Node<T>> atual = head;
    shared_ptr<Node<T>> temp = nullptr;
    shared_ptr<Node<T>> temp2 = nullptr;


    while(atual->data != d && atual->next != head){
        atual = atual->next;
    }


    if(atual->data == d){

        temp = atual->next;
        temp2 = atual->prev;
        temp->prev = temp2;
        temp2->next = temp;


        if(atual == head){
            head = temp;
        }

    } else {
        return;
    }
}

 void printList(){
    if(isEmpty()){
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
        cout << "?<-" << d << "->?"<<endl;
    }
 }

};

int main(){

    RedeSocial<string> L1;
    string comando, nome;
    ifstream arquivoE;
    ofstream arquivoS;
    arquivoE.open("redesocialinput.txt");
    arquivoS.open("saidasocial.txt");

    if(arquivoE.is_open()){
        while(true){
          arquivoE >> comando;
          if(!arquivoE) break;

          getline(arquivoE >> std::ws, nome);
          bool sucesso;

          if (comando == "ADD") {
            sucesso = L1.add(nome);

            if(sucesso) {
                arquivoS << "[ OK ] " << "ADD " << nome << endl;
            } else {
                arquivoS << "[ ERROR ] ";
            }

          }else if (comando == "REMOVE") {
            L1.remover(nome);

          }else if (comando == "SHOW") {
            L1.show(nome);
          }
        }


        arquivoE.close();
        arquivoS.close();
    }
    else{
        cout << "não foi possível abrir o arquivo" <<endl;
    }

    //L1.printList();
    /*
    L1.insertion("jose da silva");
    L1.insertion("jose da silva");
    L1.insertion("joao dos santos");
    L1.insertion("maria da penha");
    L1.remover("joao dos santos");
    L1.remover("maria da silva");
    L1.insertion("alan turing");
    L1.show("maria da penha");
    L1.show("bruno prado");
    */






    return 0;
}
