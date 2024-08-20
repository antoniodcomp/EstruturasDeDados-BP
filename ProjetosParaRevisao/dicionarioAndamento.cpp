#include <iostream>
#include <string>
#include <memory>
#include <fstream>

#define MAX_SIN 10
using namespace std;


typedef struct Palavra{

    string name;
    int sized;

}Palavra;

typedef struct Sinonimos{

    string sinonimo;

}Sinonimos;

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

    void printaLista(ofstream &arquivoS){
        shared_ptr<noPalavras> p = head;

        while(p != nullptr){
            arquivoS << p->data;
            if(p->next == nullptr)arquivoS << "";
            else arquivoS << ",";
            p = p->next;
        }
    }
};


class nodeSin{

public:
    string data;
    int bal;
    int size;
    shared_ptr<nodeSin> pai;
    shared_ptr<nodeSin> dir;
    shared_ptr<nodeSin> esq;
    listaSin sinonimos;


    nodeSin(string &d): data(d), bal(0), size(1), pai(nullptr), dir(nullptr), esq(nullptr){};

};

class Dicionary{


public:
    shared_ptr<nodeSin> root;

    Dicionary():root(nullptr){};


    shared_ptr<nodeSin> makeNode(string &str, string *arraySin, int &sizeSin){

        shared_ptr<nodeSin> newNode = make_shared<nodeSin>(str);
        /*
        if(newNode){
            for (int i = 0; i < sizeSin; i++){
                newNode->sinonimos.inserirSin(arraySin[i]);
            }
           return newNode;
        }
        else{
            cerr << "Erro ao criar o nó." << endl;
        }
        */

        return newNode;
    }

    shared_ptr<nodeSin> rotDir(shared_ptr<nodeSin> r){
        if (r == nullptr || r->dir == nullptr) {
        // Se o nó 'r' ou seu filho direito são nulos, não há necessidade de rotação
            return r;
        }

        shared_ptr<nodeSin> aux = nullptr;

        aux = r->esq;
        r->esq = aux->dir;
        if(aux->dir != nullptr) aux->dir->pai = r;
        aux->dir = r;

        return aux;

    }

    shared_ptr<nodeSin> rotEsq(shared_ptr<nodeSin> r){

        if (r == nullptr || r->dir == nullptr) {
        // Se o nó 'r' ou seu filho direito são nulos, não há necessidade de rotação
            return r;
        }
        shared_ptr<nodeSin> aux = nullptr;

        aux = r->dir;
        r->dir = aux->esq;
        if(aux->esq != nullptr) aux->dir->pai = r;
        aux->esq = r;

        return aux;
    }

    shared_ptr<nodeSin> insertNodeProcess(shared_ptr<nodeSin> root, int *aumentouAltura, string &str, string *arraySin, int &sized){

        shared_ptr<nodeSin> newNode = makeNode(str, arraySin, sized);

        if(root == nullptr){
            *aumentouAltura = 1;
            return newNode;
        }

        int compareStringResult = str.compare(root->data);

        if(compareStringResult <= 0){

            root->esq = insertNodeProcess(root->esq, aumentouAltura, str, arraySin, sized);
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
            root->dir = insertNodeProcess(root->dir, aumentouAltura, str, arraySin, sized);
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

    void insertNode(string &str, string *arraySin, int &sized){
        int aumentouAltura;

        root = insertNodeProcess(root, &aumentouAltura, str, arraySin, sized);
    }

/*
    shared_ptr<nodeSin> searchSubTree(shared_ptr<nodeSin> root, string &d, ofstream &arquivoS){

    if(root == nullptr){
        arquivoS << "?]";
        return nullptr;
    }

    if(root->data == d){
        arquivoS << d << "]";
        return root;
    }

    if(d < root->data)
    {
        arquivoS << root->data << "->";
        return searchSubTree(root->esq, d, arquivoS);
    }
    else
    {
        arquivoS << root->data << "->";
        return searchSubTree(root->dir, d, arquivoS);
    }

    }

    void searchTree(shared_ptr<nodeSin> r, string &d, ofstream &arquivoS){
        r = searchSubTree(root, d, arquivoS);

        if(r == nullptr){
            arquivoS << endl;
            arquivoS << "-";
        }
        else{
            arquivoS << endl;
            r->sinonimos.printaLista(arquivoS);
        }

    }
*/
};
/*
void percursoBusca(shared_ptr<nodeSin> root, string &d, ofstream &arquivoS){

    if(root == nullptr)return;

    if(root->data == d)return;

    if(d < root->data){

        arquivoS << root->data << "-";
        percursoBusca(root->esq, d, arquivoS);
    }
    else{
        arquivoS << root->data << "-";
        percursoBusca(root->dir, d, arquivoS);
    }

}

void in_order(shared_ptr<nodeSin> root, ofstream &arquivoS){

    if(root){
        in_order(root->esq, arquivoS);
        arquivoS <<"[" << root->data << " - ";
        //root->sinonimos.printaLista();
        in_order(root->dir, arquivoS);
    }
*/


int main(int argc, char* argv[]){
    ifstream arquivoE;
    ofstream arquivoS;
    arquivoE.open(argv[1]);
    arquivoS.open(argv[2]);

    if (!arquivoE.is_open() && !arquivoS.is_open()) {
        cerr << "Não foi possível abrir o arquivo de entrada." << endl;
        return 1; // Exit with error
    }

    int amountWords;
    Dicionary treeDicionary;

    arquivoE >> amountWords;

    string *wordList = new string[amountWords];
    string **sinList = new string*[amountWords];

    for (int i = 0; i < amountWords; i++){
        int sized;
        arquivoE >> wordList[i];
        arquivoE >> sized;

        sinList[i] = new string[sized];

        for(int j = 0; j < sized; j++){
            arquivoE >> sinList[i][j];
        }

        treeDicionary.insertNode(wordList[i], sinList[i], sized);
    }

    int consults;
    arquivoE >> consults;

    string *consultsList = new string[consults];

    for(int i = 0; i < consults; i++){
        arquivoE >> consultsList[i];
    }
/*
    for(int i = 0; i < consults; i++){
        arquivoS << "[";
        treeDicionary.searchTree(treeDicionary.root, consultsList[i], arquivoS);
        arquivoS << endl;
    }
    */

    arquivoE.close();
    arquivoS.close();

    for (int i = 0; i < amountWords; i++) {
        delete[] sinList[i];
    }

    delete[] sinList;
    delete[] wordList;
    delete[] consultsList;

    return 0;
}

