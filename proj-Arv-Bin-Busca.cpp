#include <iostream>
#include <string>
#include <memory>

using namespace std;


class Node{

public:

    string key;
    string modo;
    int tDoc;
    shared_ptr<Node>esquerda;
    shared_ptr<Node>direita;

    Node(string &k, string &m, int &t):key(k), modo(m), tDoc(t), esquerda(nullptr), direita(nullptr){};
};


class Bst{


public:
    shared_ptr<Node> root;

    Bst():root(nullptr){};


    shared_ptr<Node> criaNo(string d, string m, int t){

        shared_ptr<Node> newNode = make_shared<Node>(d, m, t);
        newNode->esquerda = nullptr;
        newNode->direita = nullptr;
        newNode->key = d;
        newNode->modo = m;
        newNode->tDoc = t;

        return newNode;
    }

    shared_ptr<Node>insertNode(shared_ptr<Node> root, string d, string m, int t){

        if(root == nullptr){
                return criaNo(d, m, t);
        }

        if(d < root->key){
            root->esquerda = insertNode(root->esquerda, d, m, t);
        }
        else if(d == root->key){

                if(root->modo == "rw"){
                    root->modo = m;
                    root->tDoc = t;
                }
        }
        else{
            root->direita = insertNode(root->direita, d, m, t);
        }

        return root;
    }


    void insertV(string d, string m, int t){
            shared_ptr<Node> newNode = make_shared<Node>(d, m, t);
            newNode->esquerda = nullptr;
            newNode->direita = nullptr;
            newNode->key = d;
            newNode->modo = m;
            newNode->tDoc = t;

            if (root == nullptr)
            {
                root = newNode;
                return;
            }

            else
            {
                shared_ptr<Node> pai = nullptr;
                shared_ptr<Node> atual = root;
                while(1)
                {
                    pai = atual;

                    if ( d.at(0) <= pai->key.at(0)){
                            atual = atual->esquerda;

                        if(d == pai->key){
                            if(pai->modo == "rw"){
                                pai->key = d;
                                pai->modo = m;
                                pai->tDoc = t;
                                return;
                            }
                        }
                        if (atual == nullptr){
                            pai->esquerda = newNode;
                            return;
                        }
                    }

                     else
                     {

                        atual = atual->direita;

                        if(d == pai->key){
                            if(pai->modo == "rw"){
                                pai->key = d;
                                pai->modo = m;
                                pai->tDoc = t;
                                return;
                            }
                        }

                        if (atual == nullptr){
                            pai->direita = newNode;
                            return;
                        }
                     }

                }
            }
    }
};

void in_order(shared_ptr<Node> root){

    if(root){
        in_order(root->esquerda);
        cout << root->key <<" "<< root->modo << " " <<root->tDoc << " " << "Bytes" << endl;
        in_order(root->direita);
    }
}

void pre_order(shared_ptr<Node> root){

    if(root){
        cout << root->key <<" "<< root->modo << " " <<root->tDoc << " " << "Bytes" << endl;
        pre_order(root->esquerda);
        pre_order(root->direita);
    }
}

void pos_order(shared_ptr<Node> root){

    if(root){
        pre_order(root->esquerda);
        pre_order(root->direita);
        cout << root->key <<" "<< root->modo << " " <<root->tDoc << " " << "Bytes" << endl;

    }
}




int main(){


    Bst b;
    shared_ptr<Node> r = nullptr;

    /*
    b.insertV("lista_ed.c", "rw",1123);
    b.insertV("senhas.txt", "rw", 144);
    b.insertV("foto.jpg", "rw", 8374719);
    b.insertV("documento.doc", "rw", 64732);
    b.insertV("lista_ed.c", "ro", 6);
    */

/*
    b.insertV("documento1", "rw", 3);
    b.insertV("documento2", "rw", 2);// Overwrites "documento1" (mode "rw")
    b.insertV("documento3", "rw", 4);
    b.insertV("documento2", "ro", 3);
*/


    b.root = b.insertNode(b.root, "lista_ed.c", "rw",1123);
    b.root = b.insertNode(b.root, "senhas.txt", "rw", 144);
    b.root = b.insertNode(b.root, "foto.jpg", "rw", 8374719);
    b.root = b.insertNode(b.root, "documento.doc", "rw", 64732);
    b.root = b.insertNode(b.root, "lista_ed.c", "ro", 1);



    in_order(b.root);
    cout<<endl;
    pre_order(b.root);
    cout<<endl;
    pos_order(b.root);




return 0;
}
