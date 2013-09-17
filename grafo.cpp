#include "grafo.hpp"
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

/* OBS: Todos os nós são identificados na entrada de 1 à N
*  e na aplicação de 0 à N-1. Nó(N) = N-1;
*/

using namespace std;

Grafo::Grafo(const char * fileName){
    nomeArquivo = fileName;
    ifstream in( fileName );
    string palavra;

    if(!in){
        printf("Nao foi possivel abrir o arquivo %s\n",fileName);
        exit(EXIT_FAILURE);
    }

    while(in >> palavra){
        if(palavra.compare("Nodes")==0){
            in >> qtdNos;
            break;
        }
    }

    listaAdj.resize(qtdNos);
    in >> palavra; //Joga Fora
    in >> qtdArestas;

    unsigned origem, destino, peso;

    for(unsigned i=0;i<qtdArestas;i++){
        in >> palavra; //lixo
        in >> origem;
        in >> destino;
        in >> peso;
        addAresta(origem-1,destino-1,peso);
        addAresta(destino-1,origem-1,peso);
    }
    in.close();
}

Grafo::Grafo(){

    cout << "Insira a quantidade de vertices" << endl;
    unsigned tam;
    cin >> tam;

    listaAdj.resize(tam);
    int no1=0,no2=0,peso;
    cout << "Insira as arestas" << endl;
    cout << "Digite pelo menos um no negativo para sair"<<endl;
    while(no1>=0 && no2>=0){
        cout << "No de origem: ";
        cin >> no1;
        cout << "No de destino: ";
        cin >> no2;
        cout << "Peso: ";
        cin >> peso;
        if(no1>=0 && no2>=0)
            addAresta(no1,no2,peso);
    }
    //imprimeLista();
}

void Grafo::addVertice(){

}


void Grafo::novoFormato(const char * fileName){
    ofstream out(fileName);
    //out.open(fileName,ofstream::out | ofstream::app);
    out << qtdNos << endl;
    //cout << "testeeee" << endl;
    for(unsigned i=0;i<listaAdj.size();i++){
        for(unsigned j=0;j<listaAdj[i].size();j++){
            out << "(" << i << "," << listaAdj[i][j].destino << "," << listaAdj[i][j].peso << ") ";
         }
    }
    out.close();
}

void Grafo::writeOutput(const char * estrategia,const char * nomeArquivo, milliseconds time,unsigned iteracoes,unsigned custo){
    ofstream out;
    out.open("resultados.txt",ofstream::out | ofstream::app);
    out << estrategia << ";" << nomeArquivo << ";" <<  qtdNos << ";" << qtdArestas << ";" << time.count() << ";" << iteracoes
    << ";" << time.count()/(float)iteracoes << ";" << custo << endl;
    out.close();
}

void Grafo::addAresta(unsigned origem,unsigned destino,unsigned peso){
    aresta novaAresta(origem,destino,peso);
    listaAdj[origem].push_back(novaAresta);
}

void Grafo::imprimeLista(){
    for(unsigned i=0;i<listaAdj.size();i++){
        for(unsigned j=0;j<listaAdj[i].size();j++)
            cout << listaAdj[i][j].origem << " " << listaAdj[i][j].destino << " " << listaAdj[i][j].peso << endl;
    }
}

Grafo::~Grafo(){

}
