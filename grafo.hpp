#ifndef GRAFO_HPP_INCLUDED
#define GRAFO_HPP_INCLUDED

#include<vector>
#include<iostream>
#include<chrono>

/* OBS: Todos os nós são identificados na entrada de 1 à N
*  e na aplicação de 0 à N-1. Nó(N) = N-1;
*/

typedef std::chrono::milliseconds milliseconds;

typedef struct aresta{
    unsigned origem;
    unsigned destino;
    unsigned peso;
    unsigned visitado; //Flag para verificar se uma dada aresta foi visitada
    aresta(unsigned a,unsigned b,unsigned c) : origem(a), destino(b), peso(c),visitado(0){};
    aresta(){};
    bool operator <(const aresta& x) const {
        return (peso < x.peso);
    }

    bool operator ==(const aresta& x) const {
        return (peso == x.peso);
    }

    bool operator >(const aresta& x) const {
        return (peso > x.peso);
    }
}Aresta;

class Grafo{
private:

public:
    Grafo(const char * fileName);
    Grafo();
    ~Grafo();
    void addVertice();
    void novoFormato(const char * fileName);
    void addAresta(unsigned origem, unsigned destino, unsigned peso);
    void imprimeLista();
    void writeOutput(const char * estrategia,const char * nome, milliseconds time,unsigned iteracoes,unsigned custo);

    std::vector<std::vector<aresta> > listaAdj;

    const char * nomeArquivo;
    unsigned qtdNos;
    unsigned qtdArestas;
 };

#endif // GRAFO_HPP_INCLUDED
