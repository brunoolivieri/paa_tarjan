#ifndef BINOMIALHEAPS_HPP_INCLUDED
#define BINOMIALHEAPS_HPP_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include "grafo.hpp"

using namespace std;

typedef struct BinHeapNode BinNode;
typedef struct BinHeapNode * BinHeap;
typedef struct BinHeapNode * Position;

struct BinHeapNode {
    int key;
    int grau;
    Aresta aresta;
    Position parent;
    Position leftChild;
    Position sibling;
};

BinHeap BinHeapExtractMin(BinHeap &heap);

BinHeap MakeBinHeap(vector<Aresta> aresta);

BinHeap BinHeapUnion(BinHeap &H1, BinHeap &H2);

BinHeap BinHeapMerge(BinHeap &H1, BinHeap &H2);

void BinLink(BinHeap &H1, BinHeap &H2);

void BinHeapDecreaseKey(BinHeap heap, BinHeap x, int key);

#endif // BINOMIALHEAPS_HPP_INCLUDED
