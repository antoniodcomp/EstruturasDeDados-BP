#include <iostream>
#include <memory>
using namespace std;

//const int qtdServ = 10;
//int  capMax;

/*define INCRE(h) (h = h == qtdServ - 1? 0: h+1)
typedef struct Requisicao{

    int numReq;
    string palavras[50];

}Requisicao;
*/


int checksum(string *str, int tam){
    int h;
    //int numStrings = sizeof(str) / sizeof(str[0]);
    for(int i = 0; i < tam; i++){
        for(char c: str[i]){
            h ^= c;
        }
    }
    return h;
}




class no{

public:
    string *data;
    shared_ptr<no> next;

    no(string *d): data(d), next(nullptr){};
};


class listaSin{
public:

    shared_ptr<no> head;
    shared_ptr<no> tail;
    int maxReq;
    int sizeT;

    listaSin():maxReq(0), sizeT(0), head(nullptr), tail(nullptr){};


    bool isEmpty(){return head == nullptr;}

    void inserirSin(string nome[]){

        shared_ptr<no> newNode = make_shared<no>(nome);
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
        //shared_ptr<no> p = head;

        while(head != nullptr){
           for(int i = 0; sizeT; i++){
            cout << head->data[i] << ", ";
           }
           head = head->next;
        }
        cout << "null";
        cout << endl;
    }
};


class Servidor{

public:
    int qtdServ;
    int capMax;
    listaSin table[100];

    Servidor(int &q, int &c):qtdServ(q), capMax(c){};

    int hash1(string *str, int tamVetor){
        int primo = 7919;
        return (primo * (checksum(str, tamVetor))) % qtdServ;
    }


    int hash2(string *str, int tamVetor){
        int primo1, primo2;
        primo1 = 104729;
        primo2 = 123;

        return (primo1 * (checksum(str, tamVetor)) + primo2) % qtdServ;
    }


    int doubleH(string *str, int ite, int tamVetor){
        int h;

        //if(h = h == qtdServ -1) return 0;
        h = (hash1(str, tamVetor) + ite*hash2(str, tamVetor)) % qtdServ;
        return h;
    }

    void insertReq(string *str, int tamVetor){
        int index = hash1(str, tamVetor);

        if(table[index].isEmpty() || table[index].maxReq < capMax){
                table[index].inserirSin(str);
                table[index].maxReq +=1;
                table[index].sizeT = tamVetor;
        }

        else{
             int cont = 0;
             while(cont < qtdServ-1){
                int n = doubleH(str, cont, tamVetor);

                 if(table[index].head == nullptr || table[index].maxReq < capMax){
                    if(table[index].maxReq < capMax){
                        table[n].inserirSin(str);
                        table[index].maxReq +=1;
                        table[index].sizeT = tamVetor;
                        break;
                     }
                 }
                cont++;
            }
        }

    }

    void printaServ(){
        for(int i = 0; i < capMax; i++){
            cout << "S" << i << ": ";
            table[i].printaLista();
        }

    }


};

int main(){

    int serv, maxR, nReq;
    cout << "Entre com a quant de servidores e a capacidade max " <<endl;
    cin >> serv;
    cin >> maxR;

    Servidor s{serv, maxR};

    cout << "Entre com a quantd de requisições" <<endl;
    cin >> nReq;
    int acc;

    while(nReq--){
        cout << "Qtd de req" <<endl;
        cin >> acc;
        string req[acc];

        for(int i = 0; i < acc; i++){
            cout << "Entre com a requisição" <<endl;
            cin >> req[i];
        }
        s.insertReq(req, acc);
    }

    s.printaServ();

return 0;
}
