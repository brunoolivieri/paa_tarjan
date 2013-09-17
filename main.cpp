#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "grafo.hpp"
#include "tarjan.hpp"

using namespace std;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

std::chrono::milliseconds refTime(5000);   // Rodar pelo menos 5 segundos
Clock::time_point t0,t1;

milliseconds tempo;

int main(int argc,char ** argv){

    if(argc<2){
        cout << "Informe uma estrutura de dados\n" << endl;
        exit(0);
    }
    unsigned iteracoes = 0;
    unsigned custo = 0;
    unsigned tipoED = (unsigned)(argv[1][0] - '0');

    for(int i = 2; i<argc;i++){
         iteracoes = 0,custo = 0;
         cout << "Arquivo de Entrada: " << argv[i] << endl;
         Grafo grafo(argv[i]);
         //Grafo grafo;

         switch(tipoED){
            case 0:{
                    cout << "Usando Heap sem Lazy" << endl;
                    t0 = Clock::now(); ///Marca Início de Tempo
                    do{
                        iteracoes++;
                        custo = tarjanHeapBinomial(grafo);
                        t1 = Clock::now(); ///Marca Fim de Tempo
                        tempo = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
                    }while(tempo<refTime);
                   grafo.writeOutput("Heap Binomial",argv[i],tempo,iteracoes,custo);
                    break;
            }case 1:{
                    cout << "Usando Heap com Lazy" << endl;
                    t0 = Clock::now(); ///Marca Início de Tempo
                    do{
                        iteracoes++;
                        custo = tarjanFibonacci(grafo);
                        t1 = Clock::now(); ///Marca Fim de Tempo
                        tempo = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
                    }while(tempo<refTime);
                   grafo.writeOutput("HEAP Fibonacci",argv[i],tempo,iteracoes,custo);
                   break;
            }default:
                    cout << "Opcao Invalida" << endl;
            }
        }
    }
