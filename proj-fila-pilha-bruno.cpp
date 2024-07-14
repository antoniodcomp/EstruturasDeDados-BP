#include <iostream>
#define MAX_DOC 50


using namespace std;

int totalPags = 0;
int totalFolhasImp = 1;

typedef struct{

    string nome;
    int folhas;
    bool valido = true;

}Documento;



typedef struct{

    Documento* pilhaDocs[MAX_DOC];
    int top;
    PilhaDoc(){
        for(int i = 0; i < MAX_DOC; i++){
            this->pilhaDocs[i] = nullptr;
        }
        this->top = -1;
    }

}PilhaDoc;


typedef struct{

    Documento* filaDocs[MAX_DOC];
    int inicio;
    int fim;
    int sizeF;

    FilaDocs(){
        for(int i = 0; i < MAX_DOC; i++){
            this->filaDocs[i] = nullptr;
        }
        this->inicio = 0;
        this->fim = 0;
        this->sizeF = 50;
    }

}FilaDocs;

typedef struct{

    string nome;
    bool livre = true;
    FilaDocs* f;
    PilhaDoc p;
    int tempoEspera;
    int folhasImp;
    int histImp;

    Impressora(){
        this->tempoEspera = 0;
        this->folhasImp = 0;
        this->histImp = 0;
    }

}Impressora;

FilaDocs filaPimpressao;
PilhaDoc empilhaFolhas;
void enqueue(Documento *d, FilaDocs *fila);
bool isEmpty(FilaDocs *d);
void filaImp(Documento *d);
void push(Documento *d);
Documento* pop(PilhaDoc *pilha);
Documento* dequeueDoc(FilaDocs *fila);

int main(){

    int nImp, nDocs;
    cout << "Entre com o numero de impressoras" <<endl;
    cin >> nImp;
    cout <<"Entre com o numero de Documentos" <<endl;
    cin>> nDocs;

    Impressora impressoras[nImp];
    Documento documentos[nDocs];

    cout << "ENTRE COM O NOME DAS IMPRESSORAS" << endl;
    for(int i = 0; i < nImp; i++){
        cin >> impressoras[i].nome;
    }
    cout << "ENTRE COM O NOME DOS DOCUMENTOS" << endl;
    for(int i = 0; i < nDocs; i++){

          cout << "Nome do Doc" <<endl;
          cin >> documentos[i].nome;
          cout << "N de folhas" << endl;
          cin >> documentos[i].folhas;
          totalPags += documentos[i].folhas;//armazeno total de p�ginas para serem impressas
          filaImp(&documentos[i]);//emfileiro os ponteiros para documentos

    }

    int i = 0;
    int j = 0;

    while(1){

     Impressora* impLivre = &impressoras[i];

       if(impLivre->tempoEspera <= 0){ //Ao inciciar o loopverifico se a impressora pode ser usada, com tempo espera menor ou igual a zero
           impLivre->livre = true;
        }

                cout << totalFolhasImp <<endl;
           if(impLivre->livre==true && filaPimpressao.inicio!= filaPimpressao.fim){ // se a impressora estiver livre e a fila de impressao não estiver vazia

                    cout << "1000";
                    j++;
                    Documento* documentoEscolhido = dequeueDoc(&filaPimpressao); // pego meu elemento um da fila

                 if(documentoEscolhido != nullptr){ // verifico se meu documento é valido
                    enqueue(documentoEscolhido, impLivre->f);//enfileiro o documento na fila de impressao da impressora

                    documentoEscolhido->folhas;
                    impLivre->livre = false;//falo que agora ela esta ocupada
                    impLivre->tempoEspera = documentoEscolhido->folhas;
                    push(documentoEscolhido);//jogo o documento na pilha de documentos impressos
                 }
            }
            else {
                impLivre->tempoEspera--;// se a impressora não estiver livre, decremento seu numero de paginas
                totalFolhasImp++;
            }

       i++;// aqui eu atualizo o contador para pegar a pr�xima impressora livre
       if(i >= nImp) i = 0; // se o contador ultrpassar o numero de impressoras v�lidas, eu reseto o contador e assim uma mesma impressora pode pegar outro documento
       if(totalFolhasImp >= totalPags) break;
    }


    for(int i = 0; i < nDocs; i++){
        Documento* d = pop(&empilhaFolhas);
        if(d == nullptr)break;
        else cout << d->nome << " " << d->folhas <<endl;
    }

return 0;
}



void enqueue(Documento *d, FilaDocs *fila){
    if(fila->inicio==fila->sizeF){
        cout<<"FILA CHEIA"<<endl;
        return;
    }
    else fila->filaDocs[fila->fim++] = d;
}

bool isEmpty(FilaDocs *d){
    if(d->inicio == d->fim)return true;
    else false;
}
void filaImp(Documento *d) {
    if(filaPimpressao.inicio == filaPimpressao.sizeF) {
        cout << "FILA CHEIA" << endl;
        return;
    }
    filaPimpressao.filaDocs[filaPimpressao.fim++] = d;
}


Documento* dequeueDoc(FilaDocs *fila) {
    Documento* documentoRetornado;

    if(fila->inicio == fila->fim) {
        return nullptr;
    } else {

        documentoRetornado = fila->filaDocs[fila->inicio++];
    }

    return documentoRetornado;
}

void push(Documento *d){

    if (empilhaFolhas.top == MAX_DOC-1) cout << "Stack Full" << endl;
    empilhaFolhas.pilhaDocs[empilhaFolhas.top++] = d;

}

Documento* pop(PilhaDoc *pilha){
    Documento* docRetornado;
     if (pilha->top == -1){
        return nullptr;
     } // stack empty
      else {
         docRetornado = pilha->pilhaDocs[--pilha->top];
         return docRetornado;
    }
}
