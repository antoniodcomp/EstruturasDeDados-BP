#include <iostream>
#include <fstream>
#define MAX_DOC 50


using namespace std;

int folhasImp = 0;
int totalDefolhas = 0;

typedef struct Documento {

   string nome;
   int folhas;
   bool valido = true;

}Documento;

typedef struct EmpilhaFolha{
    Documento documentoAtual;
    int contagemDeFolhas;
    bool valido = false;
}EmpilhaFolha;

class PilhaDoc{

public:
   Documento *vetorPilha;
   int top;
   int tamanho;

   PilhaDoc(const int &size):top(0), tamanho(size){
        vetorPilha = new Documento[size];
   }

   ~PilhaDoc() {
        delete[] vetorPilha;
    }


};

class FilaDocs{
public:
   Documento *vetorFila;
   int inicio;
   int fim;
   int sizeF;

   FilaDocs(const int &s): inicio(0), fim(0), sizeF(s){
    vetorFila = new Documento[sizeF];
   }

    ~FilaDocs() {
        delete[] vetorFila;
    }
};

class Impressora{
public:
    string nome;
    bool impressoraLivre;
    int tempoEspera;
    int folhasImp;
    int contadorImp;
    FilaDocs filaDaImpressora;
    Documento *historico;
    int documentoFinalizado;
    Documento d1;
    
/*
   Impressora():nome(""), impressoraLivre(true), tempoEspera(0), folhasImp(0), contadorImp(0), filaDaImpressora(0){
    historico = new Documento[10000];
   }
   */

   Impressora(string& n, int &pSize) : nome(n), impressoraLivre(true), tempoEspera(0), folhasImp(0), contadorImp(0), filaDaImpressora(pSize){
     historico = new Documento[pSize];
   }

   ~Impressora(){
     delete[] historico;
   }

};

struct EstadoImpressora {
    Documento documentoAtual;
    int contagemDeFolhas;
    bool documentoEmpilhado;
};

void filaInicialDocumentos(Documento &d,  FilaDocs &esperaPImp);
void empilhaNaImpressora(Documento &d, FilaDocs &fila);
bool filaEmpty(FilaDocs &fila);
Documento desempilhaFilaInicial(FilaDocs &fila);
void pushFolhasImpressas(Documento &d, PilhaDoc &pilhaImp);
Documento pop(PilhaDoc &pilha);

void verificaEmpilhamentoDocumento(EmpilhaFolha &auxiliarParaEmpilhar, PilhaDoc &pilhaImp){
   if(auxiliarParaEmpilhar.valido == true && auxiliarParaEmpilhar.documentoAtual.folhas == 0){
        pushFolhasImpressas(auxiliarParaEmpilhar.documentoAtual, pilhaImp);
        auxiliarParaEmpilhar.valido = false;
    }
}

int main(int argc, char* argv[]){
    int nImp, nDocs;
    ifstream arquivoE;
    ofstream arquivoS;
    arquivoE.open(argv[1]);
    arquivoS.open(argv[2]);

    

    arquivoE >> nImp;
    string *nomeImpressora = new string[nImp];

    for(int i = 0; i < nImp; i++){

        getline(arquivoE >> std::ws, nomeImpressora[i]);

    }

    arquivoE >> nDocs;
    Impressora **impressoras = new Impressora*[nImp];
    Documento *documentos = new Documento[nDocs];
    FilaDocs esperaPImp{nDocs};
    PilhaDoc pilhaImp{nDocs};

    //cout << impressoras[0].filaDaImpressora.sizeF <<endl;

    for(int i = 0; i <nImp; i++){
        impressoras[i] = new Impressora(nomeImpressora[i], nDocs);
    }

    //cout << impressoras[0].filaDaImpressora.sizeF <<endl;

    for(int i = 0; i < nDocs; i++){
        arquivoE >> documentos[i].nome >> documentos[i].folhas;
        totalDefolhas += documentos[i].folhas;
        filaInicialDocumentos(documentos[i], esperaPImp);
    }

    arquivoE.close();

    int i = 0;
    //int ans = 0;

EmpilhaFolha auxiliarParaEmpilhar;

while(true) {


Impressora *impLivre = impressoras[i];

    if(impLivre->tempoEspera <= 0){
      impLivre->impressoraLivre = true;
    }

    if(impLivre->impressoraLivre == true){

        Documento documentoEscolhido = desempilhaFilaInicial(esperaPImp);

         

        if(documentoEscolhido.valido == true){
            empilhaNaImpressora(documentoEscolhido, impLivre->filaDaImpressora);
            impLivre->d1 = documentoEscolhido;
            auxiliarParaEmpilhar.documentoAtual = documentoEscolhido;
            auxiliarParaEmpilhar.contagemDeFolhas = documentoEscolhido.folhas;
            //pushFolhasImpressas(auxiliarParaEmpilhar.documentoAtual,pilhaImp);
            impLivre->impressoraLivre = false;
            impLivre->documentoFinalizado = true;
            impLivre->tempoEspera = documentoEscolhido.folhas;
            impLivre->historico[impLivre->contadorImp++] = documentoEscolhido;
            arquivoS << "[" << impLivre->nome << "]";
            for(int i = impLivre->contadorImp-1; i >= 0 ; --i){
                if (i < impLivre->contadorImp - 1){ 
                    arquivoS << ",";
                }
                if(i >=0 ){
                     arquivoS << " ";
                }
                
                arquivoS << impLivre->historico[i].nome << "-" << impLivre->historico[i].folhas <<"p";
                
                    
            }
            arquivoS << endl;
            impLivre->tempoEspera--;
            folhasImp++;
            auxiliarParaEmpilhar.contagemDeFolhas--;
            
        }
   }
   else {
        impLivre->tempoEspera--;
        auxiliarParaEmpilhar.contagemDeFolhas--;
        folhasImp++;    
   }

   if(impLivre->tempoEspera <=0){
        if(impLivre->documentoFinalizado == 1){
            pushFolhasImpressas(impLivre->d1, pilhaImp);
            impLivre->documentoFinalizado = 0; 
         }
   }

    
i++;
if(i >= nImp) i = 0;
if(folhasImp >= totalDefolhas) break;
}


arquivoS << folhasImp << "p" << endl;

for(int i = 0; i < nDocs; i++){
    Documento d = pop(pilhaImp);
       if(d.nome.empty())break;
       else arquivoS << d.nome << "-" << d.folhas << "p" << endl;
}

arquivoS.close();

 for (int i = 0; i < nImp; i++) {
        delete impressoras[i];
    }

    delete[] impressoras;
    delete[] documentos;

 
 return 0;
}


void filaInicialDocumentos(Documento &d, FilaDocs &esperaPImp) {
    if(esperaPImp.inicio == esperaPImp.sizeF) {
    cout << "FILA CHEIA" << endl;
    return;
    }
    esperaPImp.vetorFila[esperaPImp.fim++] = d;
}

void empilhaNaImpressora(Documento &d, FilaDocs &fila) {
  if(fila.inicio == fila.sizeF) {
    cout << "FILA CHEIA" << endl;
    return;
 }
    fila.vetorFila[fila.fim++] = d;
}

Documento desempilhaFilaInicial(FilaDocs &fila) {
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

void pushFolhasImpressas(Documento &d, PilhaDoc &pilhaImp){

    if (pilhaImp.top == pilhaImp.tamanho) cout << "Stack Full" << endl;
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
    }
    return docRetornado;
}