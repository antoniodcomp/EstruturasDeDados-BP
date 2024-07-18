#include <iostream>
#include <memory>
#include <string>
#include <fstream>


using namespace std;



int okAdd;
int okRem;
int okShow;


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

    void add(const T& d){
        shared_ptr<Node<T>> newNode = make_shared<Node<T>>(d);


        if(isEmpty()){
            head = newNode;
            tail = newNode;
            head->next = head;
            head->prev = head;
            tail->next = tail;
            tail->prev = tail;
            okAdd = 1;
        }
        else if(head->data == d || tail->data == d){
            okAdd = 0;
            return;
        }
        else{
            newNode->next = tail->next;
            tail->next = newNode;
            newNode->prev = tail;
            head->prev = newNode;
            tail = newNode;
            okAdd = 1;
        }
    }



    void remover(const T& d){

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

        okRem = 1;

    } else {
        okRem = 0;
        return;
    }
}

 shared_ptr<Node<T>> busca(const T& d){
    shared_ptr<Node<T>> ptr = head;

    if(!ptr)return nullptr;

    do{
        if(ptr->data == d)return ptr;
        ptr = ptr->next;
    } while(ptr != head);

    return nullptr;
 }

 T show(const T& d){
    shared_ptr<Node<T>> p = busca(d);

    if(p != nullptr){
        shared_ptr<Node<T>> temp1 = nullptr;
        shared_ptr<Node<T>> temp2 = nullptr;
        temp1 = p->prev;
        temp2 = p->next;

        okShow = 1;
        return temp1->data + "<-" + p->data + "->" + temp2->data;
    }
    else{
        okShow = 0;
        return "?<-" + d + "->?";
    }
 }

};

int main(int argc, char* argv[]){

    RedeSocial<string> l1;
    string comando, nome;
    ifstream arquivoE;
    ofstream arquivoS;
    arquivoE.open(argv[1]);
    arquivoS.open(argv[2]);

    if(arquivoE.is_open() && arquivoS.is_open()){

        while(true){

          arquivoE >> comando;

          if(!arquivoE) break;

          getline(arquivoE >> std::ws, nome);

          if (comando == "ADD") {
            l1.add(nome);

            if(okAdd == 1) {
                arquivoS << "[ OK ] " << "ADD " << nome << endl;
            } else {
                arquivoS << "[ ERROR ] " << "ADD " << nome << endl;
            }
          }

          else if (comando == "REMOVE") {
            l1.remover(nome);

            if(okRem == 1) {
                arquivoS << "[ OK ] " << "REMOVE " << nome << endl;
            } else {
                arquivoS << "[ ERROR ] " << "REMOVE " << nome << endl;
            }
          }
          else if (comando == "SHOW") {
              string aux;
              aux = l1.show(nome);

              if(okShow == 1) {
                arquivoS << "[ OK ] " << aux << endl;
              } else {
                arquivoS << "[ ERROR ] " << aux << endl;
              }
          }
        }

        arquivoE.close();
        arquivoS.close();
    }
    else{
        cout << "não foi possível abrir o arquivo" <<endl;
    }


    return 0;
}
