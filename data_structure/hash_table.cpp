#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>
#include <memory.h>
#include <time.h>

int hash_size[] = {11, 113, 997};

typedef int elem_type;
typedef int key_type;
#define nullkey UINT_MAX
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1

struct hash_table {
    elem_type* elem;
    int count;
    int size_index; // index of hash_size
};

bool init_hash_table (hash_table& H) {
    H.size_index = 0;
    H.count = 0;
    H.elem = (elem_type*) malloc(sizeof(elem_type) * hash_size[H.size_index]);
    if(H.elem == nullptr) return false;
    for(int i = 0; i < hash_size[H.size_index]; ++i) {
        H.elem[i] = nullkey;
    }
    return true;
}

bool recreat_hash_table (hash_table& H) {
    H.elem = (elem_type*) realloc(H.elem, hash_size[H.size_index + 1] * sizeof(elem_type));
    if(H.elem == nullptr) return false;
    for(int i = hash_size[H.size_index]; i < hash_size[H.size_index + 1]; ++i) {
        H.elem[i] = nullkey;
    }
    ++H.size_index;
    return true;
}

int hash (hash_table& H, key_type K) {
    return (K % hash_size[H.size_index]);
}

bool collisioin (int& p, int c, int len) {
    if(c == len) return false;
    p = (p + c) % len;
    return true;
}

int hash_search (hash_table& H, key_type K, int& p, int& c) {
    c = 0;
    p = hash(H, K);
    while(H.elem[p] != nullkey && K != H.elem[p]) {
        ++c;
        if(c == hash_size[H.size_index]) {
            p = hash_size[H.size_index];
            recreat_hash_table(H);
            return UNSUCCESS;
        }
        collisioin (p, c, hash_size[H.size_index]);
    }
    if(K == H.elem[p]) return SUCCESS;
    return UNSUCCESS;
}

int insert_hash (hash_table& H, elem_type e) {
    int p, c;
    c = 0;
    if(hash_search(H, e, p, c) == SUCCESS) return DUPLICATE;
    else 
        if(c < hash_size[H.size_index] / 2) {
            H.elem[p] = e;
            H.count++;
            return 1;
        }
        else {
            recreat_hash_table(H);
            return UNSUCCESS;
        }
}

//------------------------------------

void display_hash_table (hash_table& H) {
    for(int i = 0; i < hash_size[H.size_index]; ++i) {
        if(H.elem[i] != nullkey)
            printf("%d ", H.elem[i]);
    }
}


void test() {
    int max_num = 12345678;
    hash_table H;
    init_hash_table(H);
    srand((unsigned) time(NULL));
    for(int i = 0; i < 100; ++i) {
        int num = rand() % max_num;
        while(insert_hash(H, num) == UNSUCCESS);
    }
    display_hash_table(H);
}
int main () {
    test();
    return 0;
}