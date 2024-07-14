#include <iostream>

#define MAX_DOC 50

using namespace std;

int totalPags = 0;
int totalFolhasImp = 0;


typedef struct Documento {
    string nome;
    int folhas;
    bool valido = true;
}Documento;

typedef struct PilhaDoc {
    Documento vetorPilha[MAX_DOC];
    int top = -1;
}PilhaDoc;

typedef struct Pilha {
    Documento* vetorPilha[MAX_DOC];
    int top = -1;
}Pilha;

typedef struct FilaDocs {
    Documento vetorFila[MAX_DOC];
    int inicio = 0;
    int fim = 0;
    int sizeF = MAX_DOC;
}FilaDocs;

typedef struct Impressora {
    string nome;
    bool livre = true;
    int tempoEspera = 0;
    FilaDocs f;
    Pilha hist;
    Documento vec[50];
    int folhasImp = 0;
    int histImpressao = 0;
}Impressora;

FilaDocs esperaPImp;
PilhaDoc pilhaImp;
Documento documentoEscolhido;
void filaImp(Documento &d);
void enqueue(Documento &d, FilaDocs &fila);
Documento dequeueDoc(FilaDocs &fila);
void push(Documento d);
Documento pop(PilhaDoc &pilha);
void histImpressao(Documento *d, Pilha &p);
Documento* imprimeHis(Pilha &p);

int main() {
    int nImp, nDocs;
    cout << "Entre com o numero de impressoras" << endl;
    cin >> nImp;
    cout << "Entre com o numero de Documentos" << endl;
    cin >> nDocs;

    Impressora impressoras[nImp];
    Documento documentos[nDocs];

    cout << "ENTRE COM O NOME DAS IMPRESSORAS" << endl;
    for(int i = 0; i < nImp; i++){
        cin >> impressoras[i].nome;
    }
    cout << "ENTRE COM O NOME DOS DOCUMENTOS" << endl;
    for(int i = 0; i < nDocs; i++){
        cout << "Nome do Doc" << endl;
        cin >> documentos[i].nome;
        cout << "N de folhas" << endl;
        cin >> documentos[i].folhas;
        totalPags += documentos[i].folhas;
        filaImp(documentos[i]);
    }

    int i = 0;
    int ans = 0;
    Impressora armazenaImp[nImp];

while(true) {

    Impressora impLivre = impressoras[i];
    Documento docAux;

    if(impLivre.tempoEspera <= 0){
        impLivre.livre = true;
    }

        if(impLivre.livre == true && esperaPImp.inicio!= esperaPImp.fim){

            Documento documentoEscolhido = dequeueDoc(esperaPImp);

            if(documentoEscolhido.valido == true){
                enqueue(documentoEscolhido, impLivre.f);
                impLivre.livre = false;
                impLivre.tempoEspera = documentoEscolhido.folhas;
                push(documentoEscolhido);
                //histImpressao(&documentoEscolhido, impLivre.hist);
                //Documento *dcx = imprimeHis(impLivre.hist);
                //cout << impLivre.nome << " " << dcx->nome << " " << dcx->folhas <<endl; //fazer loop dps para fazer historico
            }
        }

    else{
        impLivre.tempoEspera--;
        totalFolhasImp++;
    }

    i++;
    if(i >= nImp) i = 0; // Move to the next printer
    if(totalFolhasImp >= totalPags) break; // Break the loop if all documents are printed
}


    cout << "passou do loop" <<endl;
    cout <<totalFolhasImp<<endl;
    /*for(int i = 0; i <nImp; i++){
            cout <<armazenaImp[i].nome;
        for(int j = 0; j < 8; j++){
            cout << armazenaImp[i].f.vetorFila[j].nome << " " << armazenaImp[i].f.vetorFila[j].folhas <<endl;
        }
    }
    */
    for(int i = 0; i < nDocs; i++){
        Documento d = pop(pilhaImp);
        if(d.nome.empty())break;
        else cout << d.nome << " " << d.folhas <<endl;
    }

    return 0;
}

void enqueue(Documento &d, FilaDocs &fila) {
    if(fila.inicio == fila.sizeF) {
        cout << "FILA CHEIA" << endl;
        return;
    }
    fila.vetorFila[fila.fim++] = d;
}

void filaImp(Documento &d) {
    if(esperaPImp.inicio == esperaPImp.sizeF) {
        cout << "FILA CHEIA" << endl;
        return;
    }
    esperaPImp.vetorFila[esperaPImp.fim++] = d;
}


Documento dequeueDoc(FilaDocs &fila) {
    Documento documentoRetornado;

    if(fila.inicio == fila.fim) {
        // A fila está vazia, retorna um documento com valores padrão
        documentoRetornado.nome = "";
        documentoRetornado.folhas = 0;
        documentoRetornado.valido = false;
    } else {
        // Remove o elemento do início da fila
        documentoRetornado = fila.vetorFila[fila.inicio++];
;
    }

    return documentoRetornado;
}

void push(Documento d){

    if (pilhaImp.top == MAX_DOC-1) cout << "Stack Full" << endl;
    else pilhaImp.vetorPilha[pilhaImp.top++] = d;
}

void histImpressao(Documento *d, Pilha &p){

     if (p.top == MAX_DOC-1) {cout << "Stack Full" << endl;}
     p.vetorPilha[p.top++] = d;

}

Documento pop(PilhaDoc &pilha){
    Documento docRetornado;
     if (pilha.top == -1){
        docRetornado.folhas = 0;
        docRetornado.nome = "";
        docRetornado.valido = false;
     } // stack empty
      else {
         docRetornado = pilha.vetorPilha[--pilha.top];
         return docRetornado;
 }
}

Documento* imprimeHis(Pilha &pilha){
    Documento* docRetornado;
     if (pilha.top == -1){
        return nullptr;
     } // stack empty
      else {
         docRetornado = pilha.vetorPilha[--pilha.top];
         return docRetornado;
 }
}


