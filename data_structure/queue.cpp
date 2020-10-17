#include <cstdio>
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>
#include "status.h"

typedef int elem_type;

struct qnode {
    elem_type data;
    qnode* next;
};

typedef qnode* queue_ptr;

struct link_queue {
    queue_ptr front;
    queue_ptr rear;
};

status init_queue (link_queue &que) {
    que.rear = que.front = (queue_ptr) malloc(sizeof(qnode));
    if(!que.rear) exit(OVERFLOW);
    que.front->next = nullptr;
    return OK;
}

status destroy_queue(link_queue &que) {
    while(que.front) {
        que.rear = que.front->next;
        free(que.front);
        que.front = que.rear;
    }
    return OK;
}

status insert_queue (link_queue& que, elem_type e) {
    queue_ptr p = (queue_ptr) malloc(sizeof(qnode));
    if (!p) exit(OVERFLOW);
    p->data = e;    p->next = nullptr;
    que.rear->next = p;
    que.rear = p;
    return OK;
}

status pop_queue (link_queue& que, elem_type& e) {
    if (que.front == que.rear) return ERROR;
    queue_ptr p = que.front->next;
    e = p->data;
    que.front->next = p->next;
    if (p == que.rear) que.rear = que.front;
    free(p);
    return OK;
}

//------------------------
#define maxsize 100
struct circle_queue {
    elem_type* base;
    int front;
    int rear;
};

status init_circle_queue (circle_queue& que) {
    que.base = (elem_type*) malloc (maxsize*sizeof(elem_type));
    if(!que.base) exit(OVERFLOW);
    que.front = que.rear = 0;
    return OK;
}

status queue_length(circle_queue& que) {
    return (que.rear - que.front + maxsize) % maxsize;
}

status insert_circle_queue (circle_queue& que, elem_type e) {
    if((que.rear + 1) % maxsize == que.front) return ERROR;
    que.base[que.rear] = e;
    que.rear = (que.rear + 1) % maxsize;
    return OK;
}

status delete_circle_queue (circle_queue& que, elem_type& e) {
    if(que.front == que.rear) return ERROR;
    e = que.base[que.front];
    que.front = (que.front + 1) % maxsize;
    return OK;
} 

void test() {
    link_queue q;
    init_queue(q);
    for(int i = 0; i < 10; ++i) 
        insert_queue(q,i);
        int x;
    for(int i = 0; i < 10; i += 2) 
        pop_queue(q, x);
    queue_ptr p = q.front;
    while(p != q.rear) {
        printf("%d\n", p->data);
        p =p->next;
    }
}

void _test() {
    circle_queue q;
    init_circle_queue(q);
    for(int i = 0; i < 20; ++i) {
        insert_circle_queue(q,i);
    }
    for(int i = 0; i < 20; ++i) {
        printf("%d\n", q.base[q.front]);
        int k;
        delete_circle_queue(q, k);
    }

}

int main() {
    test(); 
    _test();

    return 0;
}