#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>

#include "BinomialHeaps.hpp"

using namespace std;

BinHeap MakeBinHeap(vector<Aresta> aresta) {
    BinHeap heap = NULL, newHeap = NULL;
    for (unsigned i = 0; i < aresta.size(); i++) {
        newHeap = (BinHeap) malloc(sizeof(BinNode));
        if (newHeap == NULL) {
            puts("Nao foi possivel alocar memoria");
            exit(1);
        }
        memset(newHeap, 0, sizeof(BinNode));
        newHeap->key = aresta[i].peso;
        newHeap->aresta = aresta[i];
        if (NULL == heap) {
            heap = newHeap;
        } else {
            heap = BinHeapUnion(heap, newHeap);
            newHeap = NULL;
        }
    }
    return heap;
}

BinHeap BinHeapUnion(BinHeap &H1, BinHeap &H2) {
    Position heap = NULL, pre_x = NULL, x = NULL, next_x = NULL;
    heap = BinHeapMerge(H1, H2);
    if (heap == NULL) {
        return heap;
    }

    pre_x = NULL;
    x = heap;
    next_x = x->sibling;

    while (next_x != NULL) {
        if ((x->grau != next_x->grau) ||
            ((next_x->sibling != NULL) && (next_x->grau == next_x->sibling->grau))) {
                pre_x = x;
                x = next_x;
        } else if (x->key <= next_x->key) {
            x->sibling = next_x->sibling;
            BinLink(next_x, x);
        } else {
            if (pre_x == NULL) {
                heap = next_x;
            } else {
                pre_x->sibling = next_x;
            }
            BinLink(x, next_x);
            x = next_x;
        }
        next_x = x->sibling;
    }
    return heap;
}

BinHeap BinHeapMerge(BinHeap &H1, BinHeap &H2) {
    BinHeap heap = NULL, firstHeap = NULL, secondHeap = NULL,
        pre_H3 = NULL, H3 = NULL;

    if (H1 != NULL && H2 != NULL){
        firstHeap = H1;
        secondHeap = H2;
       while (firstHeap != NULL && secondHeap != NULL) {
            if (firstHeap->grau <= secondHeap->grau) {
                H3 = firstHeap;
                firstHeap = firstHeap->sibling;
            } else {
                H3 = secondHeap;
                secondHeap = secondHeap->sibling;
            }

            if (pre_H3 == NULL) {
                pre_H3 = H3;
                heap = H3;
            } else {
                pre_H3->sibling = H3;
                pre_H3 = H3;
            }
            if (firstHeap != NULL) {
                H3->sibling = firstHeap;
            } else {
                H3->sibling = secondHeap;
            }
        }
    } else if (H1 != NULL) {
        heap = H1;
    } else {
        heap = H2;
    }
    H1 = H2 = NULL;
    return heap;
}

void BinLink(BinHeap &H1, BinHeap &H2) {
    H1->parent = H2;
    H1->sibling = H2->leftChild;
    H2->leftChild = H1;
    H2->grau++;
}

BinHeap BinHeapExtractMin(BinHeap &heap) {

    BinHeap pre_y = NULL, y = NULL, x = heap;
    int min = INT_MAX;
    while (x != NULL) {
        if (x->key < min) {
            min = x->key;
            pre_y = y;
            y = x;
        }
        x = x->sibling;
    }

    if (y == NULL) {
        return NULL;
    }

    if (pre_y == NULL) {
        heap = heap->sibling;
    } else {
        pre_y->sibling = y->sibling;
    }

    BinHeap H2 = NULL, p = NULL;
    x = y->leftChild;
    while (x != NULL) {
        p = x;
        x = x->sibling;
        p->sibling = H2;
        H2 = p;
        p->parent = NULL;
    }

    heap = BinHeapUnion(heap, H2);
    return y;
}
