#include "status.h"

typedef int key_type;

struct element_type{
    key_type key;
};

struct ss_table {
    element_type* elem; // 0号位留空， length按照实际长度（即计入0号位
    int length;
};

int sequential_search (ss_table& st, key_type key) {
    st.elem[0].key = key;   int i;
    for(i = st.length; st.elem[i].key != key; --i);
    return i;
}

int binary_search (ss_table& st, key_type key) {
    int left = 1, right = st.length;
    while(left <= right) {
        int mid = (left + right) >> 1;
         if(st.elem[mid].key == key) return mid;
         else if(key < st.elem[mid].key) right = mid - 1;
                else left = mid + 1;
    }
    return 0;
}

//---------------------------------------

void test() {


    return;
}

int main() {
    test();

    return 0;
}
