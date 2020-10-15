#ifndef linear_list
#define linear_list

#include <cstdio>
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>
#include "status.h"

#define list_init_size 100
#define list_increment 10

typedef int elem_type;
//--------------------------sequence_list------------------------
typedef struct {
    elem_type* elem;
    int length;
    int list_size;
} sqlist;

status init_list_sq (sqlist& L) {
    L.elem = (elem_type*) malloc(list_init_size * sizeof (elem_type));
    if (! L.elem) exit(OVERFLOW);
    L.length = 0;
    L.list_size = list_init_size;
    return OK;
}

status list_insert_sq (sqlist& L, int i, elem_type e) {
    if (i < 1 || i > L.length + 1) return ERROR;
    if (L.length >= L.list_size) {
        elem_type* newbase = (elem_type*) realloc(L.elem, (L.list_size + list_increment) * sizeof(elem_type));
        if(! newbase) exit(OVERFLOW);
        L.elem = newbase;
        L.list_size +=list_increment;
    }
    elem_type* q = &(L.elem[i - 1]);
    for (elem_type* p = &(L.elem[L.length - 1]); p >= q; --p) {
        *(p + 1) = *p;
    }
    *q = e;
    ++L.length;
    return OK;
}

status list_delete_sq (sqlist& L, int i, elem_type& e) {
    if(i < 1 || i > L.length) return ERROR;
    elem_type* p = &(L.elem[i - 1]);
    e = *p;
    elem_type* q = L.elem + L.length - 1;
    for( ; p < q; ++p) *(p) = *(p + 1);
    --L.length;
    return OK;
}

int locate_elem_sq (sqlist& L, elem_type e) {
    int i = 1;
    elem_type* p = L.elem;
    while(i <= L.length && *p != e) {
        ++i;
        ++p;
    }
    return i <= L.length ? i : 0;
}

void merge_list_sq (sqlist& La, sqlist& Lb, sqlist& Lc) {
    elem_type* pa = La.elem;
    elem_type* pb = Lb.elem;
    Lc.list_size = Lc.length = La.length + Lb.length;
    elem_type* pc = (elem_type*) malloc(Lc.length * sizeof(elem_type));
    if (!pc) exit(OVERFLOW);
    int i = 0, j = 0;
    int k = 0;
    while ( i < La.length && j < Lb.length) {
        if (*(pa + i) < *(pb + j)) {
            *(pc + (k ++)) = *(pa + (i ++));
        }
        else *(pc + (k ++))= *(pb + (j ++));
    }
    while (i < La.length) *(pc + (k ++)) = *(pa + (i ++));
    while (j < Lb.length) *(pc + (k ++)) = *(pb + (j ++));
}

//-----------------------linked_table-------------------------

struct link_node {
    elem_type data;
    link_node* next;
};

typedef link_node* link_list;

status get_elem_l (link_list L, int i, elem_type &e) {
    link_list p = L->next;  int j = 1;
    while(p && j < i) {
        p = p->next;
        ++j;
    }
    if(!p ||  j < i) return ERROR;
    e = p->data;
    return OK;
}

status list_insert_l (link_list L, int i , elem_type e) {
    link_list p = L;    int j = 0;
    while(p && j < i - 1) {
        p = p->next;
        ++j;
    }
    if(!p || j > i - 1) return ERROR;
    link_list s = (link_list) malloc(sizeof(link_node));
    s->data = e;    s->next = p->next;      p->next = s;
    return OK;
}

void creat_list_l (link_list& LL, int n) {
    LL = (link_list) malloc(sizeof(link_node));
    link_list L = LL;
    L->next = nullptr;
    for (int i = n; i > 0; --i) {
        link_list p = (link_list) malloc(sizeof(link_node));
        scanf ("%d", &p->data);
        p->next = L->next;
        L->next = p;
        L = L->next;
    }
}

status list_delete_l (link_list& L, int i, elem_type &e) {
    link_list p = L;    int j = 0;
    while (p->next && j < i - 1) {
        p = p->next;
        ++j;
    }    
    if (!(p->next) || j > i -1) return ERROR;
    link_list q = p->next;  p->next = q->next;
    e = q->data; free(q);
    return OK;
}

void merge_list_l (link_list& La, link_list& Lb, link_list& Lc) {
    link_list pa = La->next;    link_list pb = Lb->next;
    link_list pc = Lc = pa;
    while (pa && pb) {
        if (pa->data <= pb->data) {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else {
            pc->next = pb;
            pc= pb;
            pb = pb->next;
        }
    }   
    pc->next = pa ? pa : pb;
    free(Lb); // free the head pointer of the link_list B cause link_list C's head pointer is A's;
}


//--------------------------------------------
void test_sq () {
    sqlist L;
    init_list_sq(L);
    L.elem[0] = 110;
    L.length ++;
    list_insert_sq(L, 1, 2);
    printf("%d %d", L.elem[0], L.elem[1]);
}

void test_link_list() {
    link_list L;
    creat_list_l(L, 3);
    while(L) {
        L = L->next;
        printf("%d ", L->data);
    }
}

int main() {
    //test_sq();
    test_link_list();
    return 0;
}


#endif