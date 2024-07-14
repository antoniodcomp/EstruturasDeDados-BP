#include <iostream>
#include <memory>

using namespace std;

class Node{

public:
    int data;
    int chave;
    shared_ptr<Node> pai;
    shared_ptr<Node> direita;
    shared_ptr<Node> esquerda;

    Node(int d, int c): data(d),chave(c), direita(nullptr), esquerda(nullptr), pai(nullptr){};

};


class ArvoreB{

public:
    shared_ptr<Node> root;

    ArvoreB():root(nullptr){};



    void insertV(int d, int c){
        shared_ptr<Node> newNode = make_shared<Node>(d, c);
        newNode->esquerda = nullptr;
        newNode->direita = nullptr;
        newNode->data = d;
        newNode->chave = c;

        if (root == nullptr)
        {
            root = newNode;
            return;
        }

        else
        {
            shared_ptr<Node> pai = nullptr;
            shared_ptr<Node> anterior = nullptr;
            shared_ptr<Node> atual = root;
            while(1)
            {
                pai = atual;

                if (d <= pai->data){
                        atual = atual->esquerda;

                    if(d == pai->data){
                        anterior->esquerda = newNode;
                        newNode->esquerda = pai->esquerda;
                        pai = newNode;
                        return;
                        }
                        anterior = pai;
                    if (atual == nullptr){
                        pai->esquerda = newNode;
                        return;
                    }
                }

                 else
                 {
                    atual = atual->direita;

                    if(d == pai->data){
                        anterior->direita = newNode;
                        newNode->direita = pai->direita;
                        pai = newNode;
                        return;
                        }

                        anterior = pai;
                    if (atual == nullptr){
                        pai->direita = newNode;
                        return;
                    }
                 }

            }

        }

    }

    shared_ptr<Node> insertRec(shared_ptr<Node> root, int d){
        int arbitrario = 0;
        shared_ptr<Node> newNode = make_shared<Node>(d, arbitrario);

        if(root == nullptr){
            return newNode;
        }

        if(d < root->data){
            root->esquerda = insertRec(root->esquerda, d);
        }
        else{
            root->direita = insertRec(root->direita, d);
        }

        return root;
    }

    shared_ptr<Node> removeBST(shared_ptr<Node> root, shared_ptr<Node> &alvo, int d){

        shared_ptr<Node> aux = nullptr;

    if(alvo == nullptr){

        if(root == nullptr){
            return nullptr;
        }
        if(d == root->data){

            alvo = root;

            if(root->direita == nullptr && root->esquerda == nullptr){
                return nullptr;
            }
            if(root->direita == nullptr || root->esquerda == nullptr){
                if(root->esquerda == nullptr){
                    aux = root->direita;
                }
                else{
                    aux = root->esquerda;
                }
                return aux;
            }

            aux = removeBST(root->esquerda, alvo, -1);
            root = alvo;
            root->esquerda = aux;
            return root;
        }
        else{
            if(d < root->data){
                root->esquerda = removeBST(root->esquerda, alvo, d);
            }
            else{
                root->direita = removeBST(root->direita, alvo, d);
            }

            return root;
        }
    }
    else{

        if(root->direita != nullptr){

            root->direita = removeBST(root->direita, alvo, -1);
        }
        else{ //TROCA COM O MAX DA  SUBARV DIREITA;

            if(root != (alvo)->esquerda){

                root->direita = (alvo)->direita;
                aux = root->esquerda;
                root->esquerda = (alvo)->esquerda;
                alvo = root;

                return aux;
            }
            else{
                root->direita = (alvo)->direita;
                aux = root->esquerda;
                alvo = root;

                return aux;
            }
        }
        
    }

}

    void remover(int d){
        shared_ptr<Node> alvo = nullptr;

        root = removeBST(root, alvo, d);
    }
};

void in_order(shared_ptr<Node> root){

    if(root){
        in_order(root->esquerda);
        cout << root->data << " " << root->chave << endl;
        in_order(root->direita);
    }
}

void in_order_ite(shared_ptr<Node> root){

shared_ptr<Node> pilha[100];
shared_ptr<Node> p = root;
int topo = 0;

    while(p != nullptr || topo > 0){

        if(p != nullptr){
            pilha[topo++] = p;
            p = p->esquerda;
        }
        else{
            p = pilha[--topo];
            cout << p->data << " ";
            p = p->direita;
        }
    }
}

int busca(shared_ptr<Node> root, int d){

    if(root == nullptr)return -1;

    if (root->data == d)return d;

    if(d < root->data)
    {
        return busca(root->esquerda, d);
    }
    else
    {
        return busca(root->direita, d);
    }

}

int buscaIte(shared_ptr<Node> root, int d){

shared_ptr<Node> pilha[100];
shared_ptr<Node> p = root;
int topo = 0;

    while(p != nullptr && p->data != d){

        if(d < p->data){
            pilha[topo++] = p;
            p = p->esquerda;
        }
        else
        {
            pilha[topo++] = p;
            p=p->direita;
        }

    }

    return p == nullptr ? -1: p->data;
}

void contaNo(shared_ptr<Node> root, int &ans){

   if(root){
    contaNo(root->esquerda, ans);
    ans++;
    contaNo(root->direita, ans);
  }

}

int nNos(shared_ptr<Node> root)
{
    if(root == nullptr)return 0;
    return nNos(root->esquerda) + nNos(root->direita) + 1;
}

int depthT(shared_ptr<Node> root, int d){

    if(root == nullptr)return 0;
    if(d == root->data){
       return 0;
    }
    else if(d < root->data){
        return 1 + depthT(root->esquerda, d);
    }
    else{
        return 1 + depthT(root->direita, d);
    }
}
/*
int depth(shared_ptr<Node> root, int d){

    if(root == nullptr)return -1;
    if(d == root->data)return 1;

    int arvEsq = depth(root->esquerda, d);
    int arvDir = depth(root->direita, d);


}
*/


int main(){

    ArvoreB b1;

    /*int v[14] = {5, 8, 2, 3, 1, 3, 4};

    for(int i = 0; i < 6; i++){
        b1.insertV(v[i]);
        cout << "inserindo:" << endl;
    }
*/

    int a, b, c, d, e;
    a = 22;
    b = 14;
    c = 24;
    d = 7;
    e = 17;

    b1.root = b1.insertRec(b1.root, a);
    b1.root = b1.insertRec(b1.root, b);
    b1.root = b1.insertRec(b1.root, c);
    b1.root = b1.insertRec(b1.root, d);
    b1.root = b1.insertRec(b1.root, e);
    in_order(b1.root);
    cout <<endl;
    //b1.root = b1.removeBST(b1.root, b);
    b1.remover(14);
    in_order(b1.root);

    /*
    b1.insertV(31, 0);
    b1.insertV(84, 0);
    b1.insertV(15, 0);
    b1.insertV(10, 0);
    b1.insertV(0, 0);
    b1.insertV(10, 3);
    cout << "inorder" << endl;
    in_order(b1.root);
    */

    /*int x = 4;
    int prof = depthT(b1.root, x);
    cout << endl;
    cout << "a profundidade " << prof << endl;
    */
  /*  int x = 798;
    cout << endl;
    int procura = buscaIte(b1.root, x);
    cout << "numero encontrado : " << procura <<endl;
    int contaNos = 0;
    contaNo(b1.root, contaNos);
    int y = nNos(b1.root);
    cout <<"numero de nos encontrados" << contaNos << " " << y<< endl;*/


    //Escreva uma fun��o n�o recursiva que calcule o n�mero de n�s de uma �rvore bin�ria.[FEITO]
    //Escreva uma fun��o que determine a profundidade de um n� dado em rela��o � raiz da �rvore.
    //Escreva uma fun��o em C que aceite um ponteiro para um n� e retorne TRUE se esse n� for a raiz de uma �rvore bin�ria v�lida, e FALSE, caso contr�rio



return 0;
}
