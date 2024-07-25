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
    listaSin<string> *table = nullptr;
    Servidores(int &q, int &c):qtdServidores(q), capMaxReq(c){
            table = new listaSin<string>[qtdServidores];
    };

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

    ~Servidores() {

        delete[] table;
    }


};

int main(){

    int serv, maxR, nReq;
    cout << "Entre com a quant de servidores e a capacidade max " <<endl;
    cin >> serv;
    cin >> maxR;

    Servidores<string> s{serv, maxR};

    cout << "Entre com a quantd de requisições" <<endl;
    cin >> nReq;
    int acc;

    string **requisicoes =  new string*[nReq];
   int *n = new int[nReq];

    for(int i = 0; i < nReq; i++){
        cout << "Qtd de req" <<endl;
        cin >> acc;
        n[i] = acc;

        requisicoes[i] = new string[acc];

        for(int j = 0; j < acc; j++){
            cout << "Entre com a requisição" <<endl;
            cin >> requisicoes[i][j];

        }

    }

   for(int i = 0; i < nReq; i++){
     *(requisicoes+1);
     cout <<endl;
     for(int j = 0; j < n[0]; j++){
     cout << requisicoes[i][j] << "";
     s.insertReq(requisicoes[i], n[i]);
     }
     cout <<endl;
  }

    s.printaServ();





return 0;
}

