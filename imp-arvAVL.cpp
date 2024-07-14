#include <iostream>
#include <memory>

using namespace std;


class Node{

public:
    int bal;
    int data;
    int altura;
    int size;
    shared_ptr<Node> pai;
    shared_ptr<Node> dir;
    shared_ptr<Node> esq;

    Node(int d): bal(0), data(d),size(1),altura(1),pai(nullptr), dir(nullptr),esq(nullptr){};

};


class AVL {

public:
    shared_ptr<Node> root;

    AVL():root(nullptr){};


    shared_ptr<Node> rotDir(shared_ptr<Node> r){
        shared_ptr<Node> aux = nullptr;

        aux = r->esq;
        r->esq = aux->dir;
        if(aux->dir != nullptr)aux->dir->pai = r;
        aux->dir = r;

        return aux;

    }

    shared_ptr<Node> rotEsq(shared_ptr<Node> r){
        shared_ptr<Node> aux = nullptr;

        aux = r->dir;
        r->dir = aux->esq;
        if(aux->esq != nullptr)aux->dir->pai = r;
        aux->esq = r;

        return aux;
    }

    shared_ptr<Node> insertT(shared_ptr<Node> root, int *aumentouAltura, int d){

        shared_ptr<Node> newNode = make_shared<Node>(d);

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

    shared_ptr<Node> removeAVL(shared_ptr<Node> root, shared_ptr<Node> &alvo, int *diminuiu_altura, int d){
        shared_ptr<Node> aux = nullptr;
        int pela_esq;
        int desceu_esq;

        if(alvo == nullptr){ // FASE DE BUSCA

            if(root == nullptr){
                return nullptr;
            }

            if(d == root->data){

                 alvo = root;

                 if(root->esq == nullptr && root->dir == nullptr){
                    *diminuiu_altura = 1;
                    return nullptr;
                 }

                 if(root->esq == nullptr || root->dir == nullptr){
                    if(root->dir == nullptr){
                        aux = root->esq;
                    }
                    else{
                        aux = root->dir;
                    }

                    *diminuiu_altura = 1;
                    return aux;
                 }

                 //MOMENTO DE CHAMAR A SEGUNDA PARTE DA FUNÇÃO QUE FAZ O PAPEL DE TROCAR A SUBRAIZ COM O MAIOR
                 //ELEMENTO DA SUBARVORE ESQUERDA
                 //TODAVIA, O CÓDIGO FAZ A TROCA MAS NÃO SABE QUEM É ESSE VALOR DA SUBARVORE ESQUERDA """AINDA"""

                 aux = removeAVL(root->esq, alvo, diminuiu_altura, -1);
                 root = alvo;
                 desceu_esq = 1;
                 root->esq = aux;
                 return root;

                 //ESSA FUNÇÃO VAI FAZER BUSCA E TROCA DO MAIOR ELEMENTO DA SUBARVORE ESQUERDA MESMO SEM SABER AINDA
            }
            else{

                if(d < root->data){
                    root->esq = removeAVL(root->esq, alvo, diminuiu_altura, d);
                    desceu_esq = 1;
                }
                else{
                    root->dir = removeAVL(root->dir, alvo, diminuiu_altura, d);
                    desceu_esq = 0;
                }
            }
        }
        else{ // ENCONTRAR MAX alvo != nullptr

            if(root->dir != nullptr){

            root->dir = removeAVL(root->dir, alvo, diminuiu_altura, -1);
            }
            else{ //TROCA COM O MAX DA  SUBARV DIREITA;

            if(root != (alvo)->esq){

                root->dir = (alvo)->dir;
                aux = root->esq;
                root->bal = (alvo)->bal;
                root->esq = (alvo)->esq;
                alvo = root;

                return aux;
                }
            else{

                root->dir = (alvo)->dir;
                aux = root->esq;
                root->bal = (alvo)->bal;
                alvo = root;

                return aux;
                }
            }

        }

        if(*diminuiu_altura == 1){

            if(desceu_esq == 1){
                if(root->bal == 0){
                    root->bal = +1;
                    diminuiu_altura = 0;
                }
                else if(root->bal == -1){
                    root->bal = 0;
                    *diminuiu_altura = 1;
                }
                else{
                    if(root->dir->bal == 0){
                        root = rotEsq(root);
                        root->esq->bal = 1;
                        root->bal = -1;
                        *diminuiu_altura = 0;
                    }
                    else if(root->dir->bal == 1){
                        root = rotEsq(root);
                        root->esq->bal = 0;
                        root->bal = 0;
                        *diminuiu_altura = 1;
                    }
                    else{

                        root->dir = rotDir(root->dir);
                        root = rotEsq(root);

                        if(root->bal == 0){
                            root->esq->bal = 0;
                            root->dir->bal = 0;
                        }
                        else if(root->bal == +1){
                            root->esq->bal = -1;
                            root->dir->bal = 0;
                        }
                        else{
                            root->esq->bal = 0;
                            root->dir->bal = +1;
                        }

                        *diminuiu_altura = 1;
                    }
                }
            }
            else{
                if(root->bal == 0){
                    root->bal = -1;
                    *diminuiu_altura = 0;
                }
                else if(root->bal == +1){
                    root->bal = 0;
                    *diminuiu_altura = 1;
                }
                else{
                    if(root->esq->bal == 0){
                        root = rotDir(root);
                        root->dir->bal = -1;
                        root->bal = 1;
                        *diminuiu_altura = 0;
                    }

                    else if(root->esq->bal == -1){
                        root = rotDir(root);
                        root->esq->bal=0;
                        root->bal = 0;
                    }

                    else{

                        root->esq = rotEsq(root->dir);
                        root = rotDir(root);

                        if(root->bal == 0){
                            root->esq->bal = 0;
                            root->dir->bal = 0;
                        }
                        else if(root->bal == +1){
                            root->esq->bal = -1;
                            root->dir->bal = 0;
                        }
                        else{
                            root->esq->bal = 0;
                            root->dir->bal = +1;
                        }

                        *diminuiu_altura = 1;
                    }
                }
            }
        }
    }

    shared_ptr<Node> inserir(shared_ptr<Node> root, int conteudo){

        int aumentouAltura;

        return insertT(root, &aumentouAltura, conteudo);
    }

    void remover(int d){

        shared_ptr<Node> alvo = nullptr;
        int diminuiu_altura;
        root = removeAVL(root, alvo, &diminuiu_altura, d);

    }

};

void in_order(shared_ptr<Node> root){

    if(root){
        in_order(root->esq);
        cout << root->data << " ";
        in_order(root->dir);
    }
}


int main(){

    AVL b;

    b.root = b.inserir(b.root, 10);

    for(int i = 11; i < 30; i++){
        b.root = b.inserir(b.root, i);
    }

    for(int i = 9; i > 0; i--){
        b.root = b.inserir(b.root, i);
    }

    cout <<"PIO" <<endl;
    in_order(b.root);

    int patriota = 15;
    b.remover(patriota);

return 0;
}
