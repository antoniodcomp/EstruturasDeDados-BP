#include <iostream>
#include <fstream>
#include <cstdint>
#include <cmath>

using namespace std;
int chamadasbbin = 0;
int chamadasbinterp = 0;
int interpWin = 0;
int busbinWin = 0;
int totalchamadasbbin = 0;
int totalchamadasinter = 0;

class Livro{
public:
    string autor;
    string titulo;
    long isbn;

    Livro(): autor(""), titulo(""), isbn(0){}

};

int busbin(long int v[], int n, long int x){
    int i = 0;
    int f = n - 1;
    int m = (i+f)/2;
    chamadasbbin++;
    
    while(f >= i && v[m] != x){
        if(v[m] > x){
            f = m - 1;
        }
        else {
            i = m + 1;
        }
        m = (i+f)/2;
        chamadasbbin++;
        
    }

    if(v[m] == x){
        //chamadasbbin++;
        return m;
    }
    else{
        //chamadasbbin++;
        return -1;
    }
}


int heur(long int *v, int i, int f){
    return i + (v[f]-v[i]) % (f - i + 1);
}
int buscinterpol(long int v[], int n, long int x){
    int i = 0;
    int f = n-1;
    int m = heur(v, i, f);
    //chamadasbinterp++; 

    while(f >= i && v[m] != x){ // Troquei x <=v[f] && x >= v[i] por f - i + 1 != 0 funcionou, tirar duvida
        m = heur(v, i, f);
        chamadasbinterp++; 
        
        if(v[m] == x)return m;

        else if(x < v[m]){
            f = m - 1;
        }
        else {
            i = m + 1;
        }
    }

    if(v[i] == x)return i;
    else return -1;

}

int busca(long int *v, int n, long int x){
    
    int index = busbin(v, n, x);
    return index;
}

int buscaInt(long int *v, int n, long int x){

    int index = buscinterpol(v, n, x);
    return index;
}

int main(int argc, char* argv[]){
    int nLivros, nConsul;
    ifstream arquivoE;
    ofstream arquivoS;
    arquivoE.open(argv[1]);
    arquivoS.open(argv[2]);

    if (!arquivoE.is_open()) {
        cerr << "Não foi possível abrir o arquivo de entrada." << endl;
        return 1; // Exit with error
    }

    arquivoE >> nLivros;
    Livro *livros = nullptr;
    livros = new Livro[nLivros];
    long int  *tabelaIsbn = nullptr;
    tabelaIsbn = new long int[nLivros];

    for(int i = 0; i < nLivros; i++){
        string temp, input;
        arquivoE >> temp;
        livros[i].isbn = stol(temp);
        getline(arquivoE >> std::ws, input);
        size_t pos = input.find('&');
        string autor = input.substr(0, pos);
        string titulo = input.substr(pos+1);
        livros[i].autor = autor; 
        livros[i].titulo = titulo;
        tabelaIsbn[i] = livros[i].isbn;
    }

    arquivoE >> nConsul;
    long int *tabelaConsultas = nullptr;
    tabelaConsultas = new long int[nConsul];

    for(int i = 0; i < nConsul; i++){
        string temp;
        arquivoE >> temp;
        tabelaConsultas[i] = stol(temp);
    }

    arquivoE.close();

    if (!arquivoS.is_open()) {
        cerr << "Não foi possível abrir o arquivo de entrada." << endl;
        return 1; 
    }

    int index, index2;
    for(int i = 0; i < nConsul; i++){
        index = busbin(tabelaIsbn, nLivros, tabelaConsultas[i]);
        index2 = buscinterpol(tabelaIsbn, nLivros, tabelaConsultas[i]);

        totalchamadasbbin += chamadasbbin;
        totalchamadasinter += chamadasbinterp;

        if(chamadasbbin < chamadasbinterp)busbinWin++;
        else if(chamadasbinterp < chamadasbbin)interpWin++;
        else interpWin++;

        if(index != -1 && index2 != -1){
        arquivoS << "[" << tabelaConsultas[i] << "]" << "B=" << chamadasbbin <<","<< "I=" << chamadasbinterp << ":" << "Author:" << livros[index].autor << "," << "Title:" << livros[index].titulo << endl;
        }
        else{
        arquivoS << "[" << tabelaConsultas[i] << "]" << "B=" << chamadasbbin <<","<< "I=" << chamadasbinterp << ":" << "ISBN_NOT_FOUND"<<endl;
        }
        chamadasbbin = 0;
        chamadasbinterp = 0;
    }

    int mediaTB, mediaTI;
    mediaTB = floor(totalchamadasbbin/nConsul);
    mediaTI = floor(totalchamadasinter/nConsul);
    arquivoS << "BINARY=" << busbinWin <<":"<< mediaTB <<endl;
    arquivoS << "INTERPOLATION=" <<interpWin <<":"<< mediaTI <<endl;

    arquivoS.close();
 
    return 0;
}