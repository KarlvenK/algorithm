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

int stack_empty (sq_stack& s) {
    return s.base == s.top;
}

#define max_vertex_num  20

typedef char info_type;
typedef char vertex_type;


struct arc_node {
    int adjvex;
    arc_node* nextarc;
    info_type* info;
};

struct vertex_node {
    vertex_type data;
    arc_node* first_arc;
};

typedef vertex_node adjlist[max_vertex_num];

struct ALGraph {
    adjlist vertices;
    int vex_num, arc_num;
};

status topological_sort(ALGraph& G) {
    int in_degree[G.vex_num];
    for(int i = 0; i < G.vex_num; ++i) {
        for(arc_node* p = G.vertices[i].first_arc; p ; p = p->nextarc) {
            ++in_degree[p->adjvex];
        }
    }
    int count = 0;
    sq_stack s;
    init_stack(s);
    for(int i = 0; i < G.vex_num; ++i) 
        if(in_degree[i] == 0) push(s, i);
    
    while(!stack_empty(s)) {
        int t;  pop(s, t);  printf("%c\n", G.vertices[t].data);
        ++count;
        for(arc_node* p = G.vertices[t].first_arc; p ; p = p->nextarc) {
            int k = p->adjvex;
            if(!(--in_degree[k])) push(s, k);
        }
    }
    if(count != G.vex_num) return ERROR;
    return OK;
}

status topological_order(ALGraph& G, sq_stack& T, int ve[]) {
    int in_degree[G.vex_num];
    for(int i = 0; i < G.vex_num; ++i) {
        for(arc_node* p = G.vertices[i].first_arc; p ; p = p->nextarc) {
            ++in_degree[p->adjvex];
        }
    }
    int count = 0;
    sq_stack s;
    init_stack(s);
    init_stack(T);
    for(int i = 0; i < G.vex_num; ++i) 
        if(in_degree[i] == 0) push(s, i);
    
    while(!stack_empty(s)) {
        int t;  pop(s, t); push(T, t);
        ++count;
        for(arc_node* p = G.vertices[t].first_arc; p ; p = p->nextarc) {
            int k = p->adjvex;
            if(!(--in_degree[k])) push(s, k);
            if(ve[t] + *(p->info) > ve[k]) ve[k] = ve[t] + *(p->info);
        }
    }
    if(count != G.vex_num) return ERROR;
    return OK;    
}

status cirtical_path (ALGraph& G) {
    int ve[G.vex_num];  int vl[G.vex_num];
    sq_stack topo_stack;
    if(!topological_order(G, topo_stack, ve)) return ERROR;
    for(int i = 0; i < G.vex_num; ++i) vl[i] = ve[G.vex_num - 1];
    while(!stack_empty(topo_stack)) {
        int j;  arc_node* p;
        for(pop(topo_stack, j), p = G.vertices[j].first_arc; p ; p = p->nextarc) {
            int k = p->adjvex;  int dut = *(p->info);
            if(vl[k] - dut < vl[j]) vl[j] = vl[k] - dut;
        }
    }
    for(int j = 0; j <G.vex_num; ++j) {
        for(arc_node* p = G.vertices[j].first_arc; p ; p = p->nextarc) {
            int k = p->adjvex;  int dut = *(p->info);
            int ee = ve[j], el = vl[k] - dut;
            int tag = (ee == el) ? '*' : ' ';
            printf("%d %d %d %d %d %c\n", j, k, ee, el,tag);
        }
    }
    return OK;
}

void  dijkstra(ALGraph& G, int v0) {
    int f[G.vex_num] = {0};
    int dis[G.vex_num] = {0x7fffffff};
    dis[v0] = 0;    f[v0] = 1;
    for(int i = 1; i <G.vex_num; ++i) {
        int min = 0x7fffffff;   int v = -1;
        for(int j = 0; j < G.vex_num; ++j) {
            if(!f[j])
                if(min > dis[j]) {
                    min = dis[j];
                    v = j;
                }
        }
        f[v] = 1;
        for(arc_node* p = G.vertices[v].first_arc; p ; p = p->nextarc) {
            int k = p->adjvex;
            if(!f[k] && dis[v] + *(p->info) < dis[k]) {
                dis[k] = dis[v] + *(p->info);
            }
        }        
    } 
}

//-------------------------------------------------------
int main() {


    return 0;
}