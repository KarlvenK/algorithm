#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <malloc.h>
#include <memory.h>
#include <iostream>

typedef int key_type;

struct TYPE {
    key_type key;   // 关键字
    char data[20];  //数据内容
    float weigth;   //该数据被查找的频率的权值
};

typedef TYPE tree_elem_type;

struct binary_tree_node {
    tree_elem_type data;
    int bf;
    binary_tree_node *lchild, *rchild;
};

typedef binary_tree_node* binary_tree;
#define EH 0    //等高
#define LH 1    //左高
#define RH -1   // 右高

//-------------------BST--------------------------

binary_tree search_BST (binary_tree T, key_type key) {
    if ((!T) || key == T->data.key) return T;
    else 
        if(key < T->data.key) return search_BST(T->lchild, key);
        else 
            return search_BST(T->rchild, key);
}

bool search_BST (binary_tree T, key_type key, binary_tree parent, binary_tree& p) {
    if(!T) {
        p = parent;  return false;
    }
    else
        if(key == T->data.key) {
            p = T;  return true;
        }
        else 
            if(key < T->data.key) 
                return search_BST(T->lchild, key, T, p);
            else 
                return search_BST(T->rchild, key, T, p);
}

bool insert_BST (binary_tree& T, TYPE e) {
    binary_tree p;
    binary_tree_node* s;
    if(!search_BST(T, e.key, nullptr, p)) {
        s = (binary_tree_node*) malloc(sizeof(binary_tree_node));
        s->data = e; s->lchild = s->rchild = nullptr;
        if(!p) T = s;
        else 
            if(e.key < p->data.key) p->lchild = s;
            else p->rchild = s;
        return true;
    }
    else return false;
}

bool delete_BST_node(binary_tree& p) {
    binary_tree q;
    if(!p->rchild) {
        q = p;
        p = p->lchild;  //由于p是T->lchild /T->rchild的引用，所以修改p的指针等于修改T->lchild / T->rchild的指针
        free(q);
    }
    else 
        if(!p->lchild) {
            q = p;
            p = p->rchild;  //同理
            free(q);
        }
        else {                                  //难点是p点左右子树都存的情况。 
            q = p;  binary_tree s = p->lchild;  // 
            while(s->rchild) {
                q = s;                           // q记录               
                s = s->rchild;
            }
            p->data = s->data;                  //只改变被删节点p的data值，这样就不需要去管p结点做lchild和rchild的指针
            if(q != p) q->rchild = s->lchild;
            else q->lchild = s->lchild;         //特殊情况： p的左子树的根没有有右子树
            free(s);
            s = nullptr;
        }
    return true;
}

bool delete_BST (binary_tree& T, key_type key) {
    if(!T) return false;
    else {
        if(T->data.key == key) {
            return delete_BST_node(T);
        }
        else
            if(T->data.key > key) {
                return delete_BST(T->lchild, key);
            }
            else return delete_BST(T->rchild, key);
    }
}

//--------------------BBST-----------------------------------------------

void R_rotate(binary_tree& p) {
    binary_tree lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p;
    p = lc;
}

void L_rotate(binary_tree& p) {
    binary_tree rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p = rc;
}

void left_balance(binary_tree& T) {
    binary_tree lc = T->lchild;
    switch (lc->bf) {
        case LH : {
            T->bf = lc->bf = EH;
            R_rotate(T);    break;
        }
        case RH : {
            binary_tree rd = lc->rchild;
            switch (rd->bf) {
                case LH : {
                    T->bf = RH;
                    lc->bf = EH;
                    break;
                }
                case EH : {
                    T->bf = EH;
                    lc->bf = EH;
                    break;
                }
                case RH : {
                    T->bf = EH;
                    lc->bf = LH;
                    break;
                }
            }
            rd->bf = EH;
            L_rotate(T->lchild);
            R_rotate(T);
        }
    }
}

void right_balance(binary_tree& T) {
    binary_tree rc = T->rchild;
    switch (rc->bf) {
        case RH: {
            T->bf = rc->bf = EH;
            L_rotate(T);
            break;
        }
        case LH : {
            binary_tree ld = rc->lchild;
            switch (ld->bf) {
                case LH : {
                    T->bf = EH;
                    rc->bf = RH;
                    break;
                }
                case EH : {
                    T->bf = EH;
                    rc->bf = EH;
                    break;
                }
                case RH : {
                    T->bf = LH;
                    rc->bf = EH;
                    break;
                }
            }
            ld->bf = EH;
            R_rotate(T->rchild);
            L_rotate(T);
        }
    }
}

bool insert_AVL (binary_tree& T, tree_elem_type e, bool& taller) {
    if(!T) {
        T = (binary_tree) malloc(sizeof(binary_tree_node));
        T->data = e;
        T->lchild = T->rchild = nullptr;    T->bf = EH; taller = true;
    }
    else {
         if(e.key == T->data.key) {
             taller = false;
             return false;
         }
         if(e.key < T->data.key) {
             if(!insert_AVL(T->lchild, e, taller)) 
                return false;
            if(taller) {
                switch (T->bf) {
                    case LH : {
                        left_balance(T);    taller = false; break;
                    }
                    case EH : {
                        T->bf = LH; taller = true;  break;
                    }
                    case RH : {
                        T->bf = EH; taller = false;  break;
                    }
                }
            }
         }
        else {
            if(!insert_AVL(T->rchild, e, taller)) 
                return false;
            if(taller) {
                switch (T->bf) {
                    case LH : {
                        T->bf = EH; taller = false; break;
                    }
                    case EH : {
                        T->bf = RH;  taller = true;  break;
                    }
                    case RH : {
                        right_balance(T);   taller = false; break;
                    }
                }
            }
        }
    }
    return true;
}

//----------------B-树----------------------

#define bt_order 3
#define RECORD_MAX_SIZE	100		//记录中字符的最大值
typedef char Record[RECORD_MAX_SIZE];

struct Bt_node {
    int keynum;
    Bt_node* parent;
    key_type key[bt_order + 1];
    Bt_node* ptr[bt_order + 1];
    Record* recptr[bt_order + 1];
};

typedef Bt_node*    Btree;

struct result {
    Bt_node* pt; // 指向找到的结点   
    int i ;     //  1..m 
    int tag;    //  1 成功  0失败
};

int search (Btree p, key_type k) {
    int i, j;
    if(k < p->key[1]) {
        i = 0;
    }
    else 
        if(k >= p->key[p->keynum]) {
            i = p->keynum;
        }
        else {
            for(j = 1; j < (p->keynum); ++j) {
                if(k >= p->key[j] && k < p->key[j + 1]) {
                    i = j;
                    break;
                }
            }
        }
    return i;
}

result search_Btree (Btree T, key_type k) {
    Btree p = T, q = nullptr;
    int i = 0;  bool found = false;
    while (p != nullptr && !found) {
        i = search(p, k);
        if(i > 0 && p->key[i] == k) found = true;
        else {
            q = p;
            p = p->ptr[i];
        }
    }
    if(found) return {p, i, 1};
    return {q, i, 0};
}


//------------------------------------------
void test() {

}

int main() {

    return 0;
}