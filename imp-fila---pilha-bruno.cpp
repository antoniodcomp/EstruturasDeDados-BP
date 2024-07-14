#include <iostream>
#define MAX_DOC 50

using namespace std;

int totalFolhasImp = 0;
int totalPags = 0;

typedef struct Documento {

   string nome;
   int folhas;
   bool valido = true;

}Documento;

typedef struct PilhaDoc {

   Documento vetorPilha[MAX_DOC];
   int top;

}PilhaDoc;

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
    PilhaDoc folhasImpressas;
    FilaDocs filaImpressao;
    Documento historico[50];
    int folhasImp = 0;
    int contadorImp = 0;

}Impressora;


FilaDocs esperaPImp;
PilhaDoc pilhaImp;
//Documento documentoEscolhido;//
void filaImp(Documento &d);
void enqueue(Documento &d, FilaDocs &fila);
bool filaEmpty(FilaDocs &fila);
Documento dequeueDoc(FilaDocs &fila);
void push(Documento &d);
Documento pop(PilhaDoc &pilha);
//void histImpressao(Documento *d, Pilha &p);
//Documento* imprimeHis(Pilha &p);

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

while(true) {

Impressora &impLivre = impressoras[i];

  if(impLivre.tempoEspera <= 0){
    impLivre.livre = true;
    }

  if(impLivre.livre == true && filaEmpty){

    Documento documentoEscolhido = dequeueDoc(esperaPImp);

    if(documentoEscolhido.valido == true){
            enqueue(documentoEscolhido, impLivre.f);
            impLivre.livre = false;
            impLivre.tempoEspera = documentoEscolhido.folhas;
            push(documentoEscolhido);
            impLivre.historico[impLivre.contadorImp++] = documentoEscolhido;
            for(int i = impLivre.contadorImp-1; i >= 0 ; --i){
            cout <<"["<< impLivre.nome << " -> " << impLivre.historico[i].nome << " -> " << impLivre.historico[i].folhas <<"]";
            }
            cout<<endl;
            impLivre.tempoEspera--;
            totalFolhasImp++;
        }
    }
  else {
    impLivre.tempoEspera--;
    totalFolhasImp++;
    }

i++;
if(i >= nImp) i = 0;
if(totalFolhasImp >= totalPags) break;
}


cout << "passou do loop" <<endl;
cout <<totalFolhasImp<<endl;

for(int i = 0; i < nDocs; i++){
    Documento d = pop(pilhaImp);
       if(d.nome.empty())break;
       else cout << d.nome << " " << d.folhas << endl;
}

return 0;


}

bool filaEmpty(FilaDocs &fila){

    if(esperaPImp.inicio == esperaPImp.fim) return true;
    else return false;
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
    documentoRetornado.nome = "";
    documentoRetornado.folhas = 0;
    documentoRetornado.valido = false;
} else {

    documentoRetornado = fila.vetorFila[fila.inicio++];

}
    return documentoRetornado;
}

void push(Documento &d){

    if (pilhaImp.top == MAX_DOC-1) cout << "Stack Full" << endl;
    pilhaImp.vetorPilha[pilhaImp.top++] = d;

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

