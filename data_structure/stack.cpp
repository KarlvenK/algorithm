#include <cstdio>
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>
#include "status.h"

#define stack_init_size 10
#define stack_increment 10

typedef int s_elem_type;

struct sq_stack {
    s_elem_type* base;
    s_elem_type* top;
    int stack_size;
};

status init_stack (sq_stack & s) {
    s.base = (s_elem_type*) malloc(stack_init_size * sizeof(s_elem_type));
    if(!s.base) exit(OVERFLOW);
    s.top = s.base;
    s.stack_size = stack_init_size;
    return OK;
}

status get_top (sq_stack& s, s_elem_type& e) {
    if(s.top == s.base) return ERROR;
    e = *(s.top - 1);
    return OK;
}

status push (sq_stack& s, s_elem_type e) {
    if (s.top - s.base == s.stack_size) {
        s.base = (s_elem_type*) realloc (s.base, (s.stack_size + stack_increment) * sizeof(s_elem_type));
        if (!s.base) exit(OVERFLOW);
        s.top = s.base + s.stack_size;
        s.stack_size += stack_increment;
    }
    *(s.top++) = e;
    return OK;
}

status pop (sq_stack& s, s_elem_type& e) {
    if (s.top == s.base) return ERROR;
    e = *(--s.top);
    return OK;
}


void test() {
    sq_stack s;
    init_stack(s);
    for(int i = 0; i < 10; ++i) 
        push(s, i);
    //printf("%d", s.stack_size);

    //printf("%d\n%d\n%d",s.base, s.top, (s.top - s.base));

}

int main() {
    test();
    

    return 0;
}