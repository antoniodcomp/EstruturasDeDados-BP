#include <iostream>
#include <string>
#include <memory>

#define MAX_SIN 10
using namespace std;


typedef struct Palavra{

    int nSin;
    string nome;
    string sin[10];

}Palavra;

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


class no{

public:
    string data;
    shared_ptr<no> pai;
    shared_ptr<no> dir;
    shared_ptr<no> esq;
    listaSin sinonimos;


    no(string d): data(d), pai(nullptr), dir(nullptr), esq(nullptr){};

};

class Arvore{


public:
    shared_ptr<no> root;

    Arvore():root(nullptr){};


    shared_ptr<no> criaNo(string d, string *v, int qtd){

        shared_ptr<no> newNode = make_shared<no>(d);
        for (int i = 0; i < qtd; i++){
            newNode->sinonimos.inserirSin(v[i]);
        }

        return newNode;
    }

    shared_ptr<no> insertNode(shared_ptr<no> root, string d, string *v, int qtd){

        if(root == nullptr){
                return criaNo(d, v, qtd);
        }

        if(d < root->data){
            root->esq = insertNode(root->esq, d, v, qtd);
        }

        else{
            root->dir = insertNode(root->dir, d, v, qtd);
        }

        return root;
    }


    shared_ptr<no> busca(shared_ptr<no> root, string d){

    if(root == nullptr)return nullptr;

    if (root->data == d)return root;

    if(d < root->data)
    {
        return busca(root->esq, d);
    }
    else
    {
        return busca(root->dir, d);
    }

    }

};

void percursoBusca(shared_ptr<no> root, string d){

    if(root == nullptr)return;

    if (root->data == d)return;

    if(d < root->data){

        cout << root->data << "-";
        percursoBusca(root->esq, d);
    }
    else{
        cout << root->data << "-";
        percursoBusca(root->dir, d);
    }

}

void in_order(shared_ptr<no> root){

    if(root){
        in_order(root->esq);
        cout << root->data << " - ";
        //root->sinonimos.printaLista();
        in_order(root->dir);
    }

}

int main(){
    int nPal;
    Arvore a;

    cout << "Entre com a quantidade de palavras" << endl;
    cin >> nPal;

    Palavra listPala[10];

    for (int i = 0; i < nPal; i++){
        cout << "Entre com a palavra" << endl;
        cin >> listPala[i].nome;
        cout << "Entre com quantidade sinonimos" <<endl;
        cin >> listPala[i].nSin;
        for(int j = 0; j < listPala[i].nSin; j++){
            cin >> listPala[i].sin[j];
        }
        a.root = a.insertNode(a.root, listPala[i].nome, listPala[i].sin, listPala[i].nSin);
    }

    int qtd_consul;
    cout << "Digite num de consultas" <<endl;
    cin >> qtd_consul;

    string listConsultas[qtd_consul];

    for(int i = 0; i < qtd_consul; i++){
        cout << "entre com a consulta" << i <<endl;
        cin >> listConsultas[i];
    }

    for(int i = 0; i < qtd_consul; i++){
        shared_ptr<no> aux = a.busca(a.root, listConsultas[i]);
        in_order(a.root);
        cout <<endl;
        percursoBusca(a.root, listConsultas[i]);
        aux->sinonimos.printaLista();
    }
    //in_order(a.root);

    //cout << att <<endl;
    return 0;
}

