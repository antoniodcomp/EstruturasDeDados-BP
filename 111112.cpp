#include <iostream>
#include <memory>
#include <limits>
#include <vector>


using namespace std;

template <typename T>
class no{
public:

    T *data;
    int tam;
    shared_ptr<no<T>> next;

    no(T *d, int &tam): data(d), tam(tam), next(nullptr){};
};

template <typename T>
int checksum(T *str, int tam){
    int h = 0;
    int x;
    //int numStrings = sizeof(str) / sizeof(str[0]);
    for(int i = 0; i < tam; i++){
        for(char c: str[i]){
            x ^= c;
        }
        h += x;
    }
    return h % 256;
}

template <typename T>
class listaSin{
public:

    shared_ptr<no<T>> head;
    shared_ptr<no<T>> tail;
    int atualReq; // CADA SERVIDOR TEM UMA CAPACIDADE MÁX DE REQUI
    //int sizeT;

    listaSin():atualReq(0), head(nullptr), tail(nullptr){};


    bool isEmpty(){return head == nullptr;}

    void inserirSin(T *nome, int sizeT){

        shared_ptr<no<T>> newNode = make_shared<no<T>>(nome, sizeT);
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
        shared_ptr<no<T>> p = head;

        while(p != nullptr){
           for(int i = 0; i < p->tam; i++){
            cout << p->data[i] << " ";
           }
           p = p->next;
        }
        //cout << "null";
        cout << endl;
    }
};
int qtdServidores;

template <typename T>
class Servidores{

public:
    int qtdServidores;
    int capMaxReq; // capacidade max que cada servidor vai ter
    listaSin<string> table[50];
    Servidores(int &q, int &c):qtdServidores(q), capMaxReq(c){};

    int hash1(T *str, int tamVetor){
        int primo = 7919;
        return (primo * (checksum(str, tamVetor))) % qtdServidores;
    }


    int hash2(T *str, int tamVetor){
        int primo1, primo2;
        primo1 = 104729;
        primo2 = 123;

        return (primo1 * (checksum(str, tamVetor)) + primo2) % qtdServidores;
    }

    int doubleH(T *str, int ite, int tamVetor){
        int h;

        //if(h = h == qtdServ -1) return 0;
        h = (hash1(str, tamVetor) + ite*hash2(str, tamVetor)) % qtdServidores;
        return h;
    }

    void insertReq(T *str, int tamVetor){
        int index = hash1(str, tamVetor);

        if(table[index].atualReq < capMaxReq){
            if(table[index].atualReq < capMaxReq){
                table[index].inserirSin(str, tamVetor);
                table[index].atualReq ++;
                //table[index].sizeT += tamVetor;
            }
        }
        else{
             int cont = 0;
             while(cont < qtdServidores-1){
                int n = doubleH(str, cont, tamVetor);

                 if(table[n].head == nullptr){
                    if(table[n].atualReq < capMaxReq){
                        table[n].inserirSin(str, tamVetor);
                        table[n].atualReq +=1;
                        //table[n].sizeT += tamVetor;
                        break;
                     }
                 }
                cont++;
            }
        }
    }

    void printaServ(){ // PROBLEMA ESTÁ AQUI
        for(int i = 0; i < qtdServidores; i++){
            cout << "S" << i << ": ";
            table[i].printaLista();
        }
    }

    void printaInd(T *str, int tamVetor){
        int index = hash1(str, tamVetor);
        cout << index <<endl;
        table[index].printaLista();
    }


};



int main(){

    int servidores, capServidores, nReq, sz;

    cout << "Entre com a qtd servidores" <<endl;
    cin >> servidores;
    cout << "Entre com a cap max de servidores" <<endl;
    cin >> capServidores;

    Servidores<string> s{servidores, capServidores};
    cout << "Informe n de requisições" <<endl;
    cin >> nReq;

    //int listaTam[10];

    /*
    for(int i = 0; i < nReq; i++){
        cout << "Entre com quantidade da requisição" <<endl;
        cin >> sz;
        listaTam[i] = sz;
       for(int j = 0; j < sz; j++){
            cin >> lista[i][j];
       }
    }

    for(int i = 0; i < nReq; i++){
        s.insertReq(lista[i], listaTam[i]);
    }
*/
/*
    vector<vector<string>> lista = {{"ufs"},{"a", "b", "c"},{"cd", "ef"},{"e", "d"},{"hash"}};

    int listaTam[10] = {1,3, 2, 2, 1};
    for(int i = 0; i < nReq; i++){
        s.insertReq(lista[i], listaTam[i]);
    }
    */



    string nome[1] = {"ufs"};
    string nome1[3] = {"a","b", "c"};
    string nome2[2] = {"cd", "ef"};
    string nome3[2] = {"e", "d"};
    string nome4[1] = {"hash"};

    int a, b, c, d, e;
    a = 1;
    b = 3;
    c = 2;
    d = 2;
    e = 1;

    s.insertReq(nome, a);
    s.insertReq(nome1, b);
    s.insertReq(nome2, c);
    s.insertReq(nome3, d);
    s.insertReq(nome4, e);
    s.printaServ();



    return 0;
}
