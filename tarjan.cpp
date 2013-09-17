#include "BinomialHeaps.hpp"
#include "grafo.hpp"
#include "fibonacci.hpp"

unsigned min(unsigned a, unsigned b){
    return a<b ? a : b;
}

unsigned max(unsigned a,unsigned b){
    return a>b ? a : b;
}

unsigned findGrupo(vector<unsigned> grupos,unsigned pos){
    unsigned atual = pos;
    while(grupos[atual]!=atual){
        atual = grupos[atual];
    }
    return atual;
}

void grupoUnion(vector<unsigned> &grupos,unsigned grupoA, unsigned grupoB){
    if(grupoA<grupoB)
        grupos[grupoB] = grupoA;
    else if(grupoA>grupoB)
        grupos[grupoA] = grupoB;
    else
        cout << "Erro na Uniao dos grupos!!!" << endl;
}

unsigned tarjanHeapBinomial(Grafo grafo){
    ///Lista de adjacência
    vector<vector<aresta> > adj = grafo.listaAdj;
    ///Grupos Disjuntos
    vector<unsigned> grupo;
    ///Grupo que ainda não foram eliminados pela operação de merge
    vector<bool> valido(adj.size(),true);
    ///Heap
    vector<BinHeap> h;

    unsigned custoMST = 0;

    ///Cria grupos disjuntos
    for(unsigned i=0; i<adj.size(); i++){
        grupo.push_back(i);
        h.push_back(MakeBinHeap(adj[i]));
    }

    while(h.size()>1){
        ///Seleciona a última heap - Análise de traz para frente
        BinHeap h1 = h.back();
        Aresta arestaAtual;
        unsigned grupoA;
        unsigned grupoB;

        ///Verifica quais grupos devem ser unidos (merge)
        do{
            arestaAtual = BinHeapExtractMin(h1)->aresta;
            grupoA = findGrupo(grupo,arestaAtual.origem);
            grupoB = findGrupo(grupo,arestaAtual.destino);

        }while(grupoA==grupoB || !valido[grupoA] || !valido[grupoB]);

        /// Verifica se a aresta conecta grupos diferentes
        h[grupoA] = h1;
        ///Merge dos grupos
        h[min(grupoA,grupoB)] = BinHeapUnion(h[grupoA],h[grupoB]);

        h.pop_back(); ///Remove o último grupo
        valido[max(grupoA,grupoB)] = false; ///Torna o grupo de maior ID inválido
        grupoUnion(grupo,grupoA,grupoB); ///Une os dois grupos disjuntos no grupo de menor ID

        custoMST += arestaAtual.peso; /// Atualiza o peso total da MST
    }
    return custoMST;
}

unsigned tarjanFibonacci(Grafo grafo){
    ///Lista de adjacência
    vector<vector<aresta> > adj = grafo.listaAdj;
    ///Grupos Disjuntos
    vector<unsigned> grupo;
    ///Grupo que ainda não foram eliminados pela operação de merge
    vector<bool> valido(adj.size(),true);
    ///Heap de Fibonacci
    vector<FibonacciHeap<Aresta> > h(adj.size());

    unsigned custoMST = 0;

    ///Cria grupos disjuntos
    for(unsigned i=0; i<adj.size(); i++){
        grupo.push_back(i);
        for(unsigned j=0; j<adj[i].size(); j++)
            h[i].insert(adj[i][j]);
    }

    while(h.size()>1){
        Aresta arestaAtual;
        unsigned grupoA;
        unsigned grupoB;

         ///Verifica quais grupos devem ser unidos (merge)
        do{
            arestaAtual = h.back().removeMinimum();
            grupoA = findGrupo(grupo,arestaAtual.origem);
            grupoB = findGrupo(grupo,arestaAtual.destino);

        }while(grupoA==grupoB || !valido[grupoA] || !valido[grupoB]);

        ///Merge dos grupos
        h[grupoB].merge(h[grupoA]);

        h.pop_back(); ///Remove o último grupo
        valido[max(grupoA,grupoB)] = false; ///Torna o grupo de maior ID inválido
        grupoUnion(grupo,grupoA,grupoB); ///Une os dois grupos disjuntos no grupo de menor ID

        custoMST += arestaAtual.peso; /// Atualiza o peso total da MST
    }
    return custoMST;
}
