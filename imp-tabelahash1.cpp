#include <iostream>
#include <memory>
#include <string>

#define MAX_LIST 100

using namespace std;

template <typename T>
class Node{
public:

    T data;
    string key;
    shared_ptr<Node<T>> next;

    Node(const T &d, const string &k): data(d), key(k), next(nullptr){};

};


int funcHash(const string &k){
    int primo = 127;
    int h = 0;
    char c;

    for(char c : k){
        h = (h * primo + c) % MAX_LIST;
    }
    return h;
}


template <typename T>
class hashTable{

public:

    static const int MAX_LISTA = 100;
    shared_ptr<Node<T>> hashL[MAX_LISTA];

    hashTable(){
        for(int i = 0; i < MAX_LIST; i++){
            hashL[i] = nullptr;
        }
    }

    void insertNode(const T &v, const string &k){
        int index = funcHash(k);
        shared_ptr<Node<T>> no = make_shared<Node<T>>(v, k);
        shared_ptr<Node<T>> node = hashL[index];
        shared_ptr<Node<T>> newNode = no;

        if(node == nullptr){
            hashL[index] = newNode;
        }

        else{

            while(node != nullptr){
                if(node->next == nullptr){
                    node->next = newNode;
                    break;
                }

                node = node->next;
            }
            
        }
    }

    T searchNode(const string &k){

        int index = funcHash(k);
        shared_ptr<Node<T>> atual = hashL[index];

        while(atual != nullptr){
            if (atual->key == k)return atual->data;

         atual = atual->next;
        }

        return T();
    }
};

int main(){

    string C, j;
    hashTable<string> h;
    h.insertNode("bruno", "prado");
    h.insertNode("fabio", "akita");
    C = h.searchNode("prado");
    j = h.searchNode("akita");

    cout << C << j << endl;


    return 0;
}
