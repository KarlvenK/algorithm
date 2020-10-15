#ifndef status_h
#define status_h

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#include <memory.h>
#include <stdlib.h>


typedef int status;
typedef int elem_type;
typedef elem_type* triplet;

status init_triplet (triplet& T, elem_type v1, elem_type v2, elem_type v3) {
    T = (elem_type*) malloc(3 * sizeof(elem_type));
    if (! T) exit(OVERFLOW);
    T[0] = v1;   T[1] = v2;  T[2] = v3;
    return OK;
}

status destroy_triplet (triplet& T) {
    free(T);    T = nullptr;
    return OK;
}

status get (triplet& T, int i, elem_type& e) {
    if(i < 1 || i > 3) return ERROR;
    e = T[i - 1];
    return OK;
}

status put (triplet& T, int i, elem_type e) {
    if(i < 1 || i > 3) return ERROR;
    T[i - 1] = e;
    return OK;
}

status is_ascending (triplet& T) {
    return (T[0] <= T[1] && T[1] <= T[2]);
}

status is_descending (triplet& T) {
    return (T[0] >= T[1] && T[1] >= T[2]);
}

status Max (triplet& T, elem_type& e) {
    if(T[0] > T[1]) 
        e = T[0] > T[2] ? T[0] : T[2];
    else
        e = T[1] > T[2] ? T[1] : T[2];
    return OK;
}

status Min(triplet& T, elem_type& e) {
    if(T[0] > T[1])
        e = T[1] < T[2] ? T[1] : T[2];
    else 
        e = T[0] < T[2] ? T[0] : T[2];
    return OK;
}

#endif
