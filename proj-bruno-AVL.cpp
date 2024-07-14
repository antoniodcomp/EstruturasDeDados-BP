#include <iostream>
#include <string.h>
#include <memory>

#define MAX_PALAVRAS 10

using  namespace std;



class noPalavras{

public:

    string data;
    shared_ptr<noPalavras> next;

    noPalavras(string d): data(d), next(nullptr){};

};

class listaSin{
public:

    shared_ptr<noPalavras> head;
    shared_ptr<noPalavras> tail;

    listaSin(): head(nullptr), tail(nullptr){};


    bool isEmpty(){
        if(head == nullptr)return true;
        else return false;
    }

    void inserirSin(string nome){

        shared_ptr<noPalavras> newNode = make_shared<noPalavras>(nome);
        if(isEmpty()){
            newNode->next = head;
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        }
    }

    void printaLista(){
        shared_ptr<noPalavras> p = head;

        while(p != nullptr){
            cout << p->data << " -> ";
            p = p->next;
        }
        cout << "null";
        cout << endl;
    }
};

class noAVL{

public:
    string data;
    int bal;
    shared_ptr<noAVL> dir;
    shared_ptr<noAVL> esq;
    shared_ptr<noAVL> pai;
    shared_ptr<noPalavras> sinonimos[MAX_PALAVRAS];

    noAVL(string d): data(d), bal(0), pai(nullptr), dir(nullptr), esq(nullptr){
        for(int i = 0; i < MAX_PALAVRAS; i++){
            sinonimos[i] = nullptr;
        }
    }

};
/*
class ArvorePalavras{

    shared_ptr<noAVL> root;

    ArvorePalavras(): root(nullptr){};

shared_ptr<noAVL> rotDir(shared_ptr<noAVL> r){
        shared_ptr<noAVL> aux = nullptr;

        aux = r->esq;
        r->esq = aux->dir;
        if(aux->dir != nullptr)aux->dir->pai = r;
        aux->dir = r;

        return aux;

    }

    shared_ptr<noAVL> rotEsq(shared_ptr<noAVL> r){
        shared_ptr<noAVL> aux = nullptr;

        aux = r->dir;
        r->dir = aux->esq;
        if(aux->esq != nullptr)aux->dir->pai = r;
        aux->esq = r;

        return aux;
    }

    shared_ptr<noAVL> insertT(shared_ptr<noAVL> root, int *aumentouAltura, int d){

        shared_ptr<noAVL> newNode = make_shared<noAVL>(d);

        if(root == nullptr){
            *aumentouAltura = 1;
            return newNode;
        }
        if(d < root->data){

            root->esq = insertT(root->esq,aumentouAltura, d);
            root->esq->pai = root;

            if(*aumentouAltura == 1){

                if(root->bal == 1){
                    root->bal = 0;
                    *aumentouAltura = 0;
                }
                else if(root->bal == 0){
                    root->bal = -1;
                    *aumentouAltura = 1;
                }
                else {
                    if(root->esq->bal == (-1)){
                        root = rotDir(root);
                        root->dir->bal=0;
                    }
                    else {
                        root->esq = rotEsq(root->esq);
                        root = rotDir(root);

                        if(root->bal == 0){
                            root->esq->bal=0;
                            root->dir->bal=0;
                        }
                        else if(root->bal == -1){
                            root->esq->bal=0;
                            root->dir->bal=1;
                        }
                        else{
                            root->esq->bal=-1;
                            root->dir->bal=0;
                        }
                    }
                    *aumentouAltura = 0;
                    root->bal = 0;
                }
            }
        }
        else{
            root->dir = insertT(root->dir,aumentouAltura, d);
            root->dir->pai = root;

            if(*aumentouAltura == 1){

                if(root->bal== -1){
                    root->bal=0;
                    *aumentouAltura = 0;
                }
                else if(root->bal == 0){
                    root->bal=1;
                    *aumentouAltura=1;
                }
                else{
                    if(root->dir->bal == 1){
                        root = rotEsq(root);
                        root->esq->bal = 0;
                    }
                    else{
                        root->dir=rotDir(root->dir);
                        root = rotEsq(root);

                        if(root->bal == 0){
                            root->esq->bal=0;
                            root->dir->bal=0;
                        }
                        else if(root->bal == -1){
                            root->esq->bal=0;
                            root->dir->bal=1;
                        }
                        else{
                            root->esq->bal=-1;
                            root->dir->bal=0;
                        }
                    }

                    *aumentouAltura = 0;
                    root->bal = 0;
                }

            }

        }
        return root;
    }

    shared_ptr<noAVL> inserir(shared_ptr<noAVL> root, int conteudo){

        int aumentouAltura;

        return insertT(root, &aumentouAltura, conteudo);
    }

};

*/

int main(){

    listaSin l;

    l.inserirSin("bahia");
    l.inserirSin("cauly");
    l.inserirSin("everton");

    l.printaLista();

    return 0;

}
