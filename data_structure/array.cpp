#include <cstdio>
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdarg.h>
#include "status.h"

#define max_arr_dim 8

typedef int elem_type;

struct Array {
    elem_type* base;
    int dimension;
    int* bounds;
    int* constants;
};

status init_arr(Array& a, int dimension, ...) {
    if(dimension < 0 || dimension > max_arr_dim) 
        return ERROR;
    a.dimension = dimension;
    a.bounds = (int*) malloc(dimension * sizeof(int));
    if(!a.bounds) 
        exit(OVERFLOW);
    int elem_total = 1;
    va_list ap;
    va_start(ap, dimension);
    for (int i = 0; i < dimension; ++i) { //求出数组大小
        a.bounds[i] = va_arg(ap, int);    //读入每一维度的长度
        if(a.bounds[i] < 0) 
            return ERROR;
        elem_total *= a.bounds[i];        //总容量 = Π (维度i长度)
    }
    va_end(ap);
    /*
        loc(j1, j2, j3, j4, ...,jn) = loc(0,0,0...,0) + (b2* b3 * b4 ...* bn * j1 + b3 * b4 * ... * bn + ...  + 1 * jn)
        我们只需要把 (Π bi) 看成一个常熟ci，提前处理好即可
        易得i越小 ci越大
    */
    a.base = (elem_type*) malloc(elem_total * sizeof(elem_type));
    if(!a.base) exit(OVERFLOW);
    a.constants = (int*) malloc(dimension * sizeof(int));
    if(!a.constants) exit(OVERFLOW);
    a.constants[dimension - 1] = 1;
    for(int i = dimension - 2; i >= 0; --i) 
        a.constants[i] = a.bounds[i + 1] * a.constants[i + 1];
    return OK;
}

status destroy_arrary(Array& a) {
    if(!a.base) return ERROR;
    free(a.base);
    a.base =nullptr;
    if(!a.bounds) return ERROR;
    free(a.bounds);
    a.bounds = nullptr;
    if(!a.constants) return ERROR;
    free(a.constants);
    a.constants = nullptr;
    return OK;
}

status locate(Array& a, va_list ap, int& offset) {
    offset = 0;
    for(int i = 0; i < a.dimension; ++i) {
        int index = va_arg(ap, int);
        if(index < 0 || index >= a.bounds[i]) return ERROR;
        offset += a.constants[i] * index;        
    }
    return OK;
}

status value(Array& a, elem_type& e, ...) {
    va_list ap;
    va_start(ap,e);
    int offset;
    int result = locate(a, ap, offset);
    if(result <= 0) return result;
    e = *(a.base + offset);
    return OK;
}

status assign_array(Array& a, elem_type e, ...) {
    int result, offset;
    va_list ap;
    va_start(ap, e);
    result = locate(a, ap, offset);
    if(result <= 0) return result;
    *(a.base + offset) = e;
    return OK;
}

//--------------------------------------

void test() {
    Array f;
    init_arr(f, 3, 10, 10, 10);
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j) 
            for(int k = 0; k < 10; ++k) 
                assign_array(f, i * j * k, i, j, k);
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            for(int k = 0; k < 10; ++k) {
                int e;
                value(f, e, i, j, k);
                if(e != i * j * k) printf("fuck me!");
                printf("%d ",e);
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main() {
    test();
    return 0;
}