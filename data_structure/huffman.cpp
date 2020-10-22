#include "status.h"
#include <string.h>

struct huffmanTreeNode {
    unsigned int weight;
    unsigned int parent, lchild, rchild;
};
typedef huffmanTreeNode*    huffmanTree;
typedef char**      huffmanCode;

void max(huffmanTree ht, int& s1, int& s2, int n) {
    if(ht[s1].weight <= ht[s2].weight) {
        if(ht[n].weight < ht[s2].weight)
            s2 = n;
    }
    else {
        if(ht[n].weight < ht[s1].weight)
            s1 = n;
    }
}

void select(huffmanTree ht, int n, int& s1, int& s2) {
    int i;
    for(i = 1; i <= n; ++i) {
        if(ht[i].parent == 0) {
            if(s1 == 0) s1 = i;
            else 
                if(s2 == 0)
                    s2 = i;
                else
                    max(ht, s1, s2, i);
        }
    }
    if(s1 > s2) {
        i = s1;
        s1 = s2;
        s2 = i;
    }
}

void huffmanCoding(huffmanTree& ht, huffmanCode&hc, int* w, int n) {
    if(n <= 1) return;
    int m = 2 * n - 1;
    ht = (huffmanTree) malloc(sizeof(huffmanTreeNode) * (m + 1));
    huffmanTree p;
    int i;
    for(p = ht + 1, i = 1; i <= n; ++i,++p, ++w) {
        p->weight = *w;
        p->lchild = p->rchild = p->parent = 0;
    }
    for( ; i <= m; ++i, ++p) {
        p->weight = p->parent = p->lchild = p->rchild = 0;
    }
    for(i = n + 1; i <= m; ++i) {
        int s1 = 0, s2 = 0;
        select(ht, i - 1, s1, s2);
        ht[s1].parent = i;
        ht[s2].parent = i;
        ht[i].lchild = s1;
        ht[i].rchild = s2;
        ht[i].weight = ht[s1].weight +ht[s2].weight;
    }
    hc = (huffmanCode) malloc((n + 1) * sizeof(char*));
    char* cd = (char*) malloc(n * sizeof(char));
    cd[n - 1] = '\0';
    for(i = 1; i <= n; ++i) {
        int start = n - 1;
        for(int cur = i, further = ht[i].parent; further != 0;
        cur = further, further = ht[further].parent) {
            if(cur == ht[further].lchild)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        }
        hc[i] = (char*) malloc((n - start) * sizeof(char));
        strcpy(hc[i], &cd[start]);
    }
    free(cd);
    cd = nullptr;
}

void getHuffmanCode(huffmanTree ht, huffmanCode& hc, int n) {
    int codeLen, i;
    char p; char* code;
    hc = (huffmanCode) malloc((n + 1) * sizeof(char*));
    code = (char*) malloc(n * sizeof(char));
    p = 2 * n - 1;
    for(i = 1; i <= p; ++i) 
        ht[i].weight = 0;
    while(p) {
        if(ht[p].weight == 0) {
            ht[p].weight = 1;
            if(ht[p].lchild != 0) {
                p = ht[p].lchild;
                code[codeLen++] = '0';
            }
            else 
                if(ht[p].rchild == 0) {
                    hc[p] = (char*) malloc(sizeof(char));
                    code[codeLen] = '\0';
                    strcpy(hc[p], code);
                }
        }
        else 
            if(ht[p].weight == 1) {
                ht[p].weight = 2;
                if(ht[p].rchild != 0) {
                    p = ht[p].rchild;
                    code[codeLen++] = '1';
                }
            }
            else {
                ht[p].weight = 0;
                p = ht[p].parent;
                codeLen--;
            }
    }

}

//----------------------

void test() {


    return;
}

int main() {

    return 0;
}