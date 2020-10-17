#include <cstdio>
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>
#include "status.h"

//-------------------string built by struct---------有毛病

#define max_string_len 255
typedef char string[max_string_len + 1];
inline int min(int a, int b) {
    return a < b ? a : b;
}

void assign_string(string& s, char* chs) {
    int len = 0;
    while(*chs) {
        ++len;
        s[len] = *chs;
        ++chs;
    }
    s[0] = len;
}

status concat (string& ret, string s1, string s2) {
    bool uncut = true;
    if (s1[0] + s2[0] <= max_string_len) {
        ret[0] = s1[0] + s2[0];
        for (int i = 1; i <= s1[s1[0]]; ++i) ret[i] = s1[i];
        for (int i = 1; i <= s2[0]; ++i) {
            ret[s1[s1[0] + i]] = s2[i]; 
        }
        uncut = true;
    }
    else {
        if (s1[0] < max_string_len) {
            for (int i = 1; i <= s1[0]; ++i) ret[i] = s1[i];
            for (int i = s1[0] + 1; i <= max_string_len; ++i) 
                ret[i] = s2[i - s1[0]];
            uncut = false;
        }
        else {
            for (int i = 1; i <= max_string_len; ++i) 
                ret[i] = s1[i];
            ret[0] = max_string_len;
            uncut = false;
        }
    }
    return uncut;
}

status sub_string (string & sub, string s, int pos, int len) {
    if (pos < 1 || pos > s[0] || len < 0 || len > s[0] - pos + 1) return ERROR;
    for (int i = pos; i < pos + len; ++i) {
        sub[i - pos + 1] = s[i];
    }
    sub[0] = len;
    return  OK;
}

//------------------无视上面的屎---------------------------------

struct heap_string {
    char* ch;
    int length;
};

status str_assign(heap_string& s, char* chars) {
    if (s.ch) free(s.ch);
    char* c = chars;
    int len = 0;
    for(; *c; ++len, ++c);
    if (!len) {
        s.ch = nullptr;
        s.length = 0;
    }
    else {
        s.ch = (char*) malloc(len * sizeof(char));
        if (!s.ch) exit(OVERFLOW);
        for(int i = 0; i < len; ++i) {
            s.ch[i] = chars[i];
        }
        s.length = len;
    }
    return OK;
}

int str_length(heap_string s) {
    return s.length;
}

int str_compare(heap_string s, heap_string t) {
    for(int i = 0; i < min(s.length, t.length); ++i) {
        if(s.ch[i] != t.ch[i]) return s.ch[i] - t.ch[i];
    }
    return s.length - t.length;
}

status clear_string(heap_string& s) {
    if (s.ch) {
        free(s.ch);
        s.ch = nullptr;
    }
    s.length = 0;
    return OK;
}

status str_concat(heap_string& ans, heap_string s, heap_string t) {
    if (ans.ch) free(ans.ch);
    ans.ch = (char*) malloc((s.length + t.length) * sizeof (char));
    if (!ans.ch) exit(OVERFLOW);
    for(int i = 0; i < s.length; ++i)
        ans.ch[i] = s.ch[i];
    for(int i = 0; i < t.length; ++i) 
        ans.ch[s.length + i] = t.ch[i];
    ans.length = s.length + t.length;
    return OK;
}

status str_sub(heap_string& ans, heap_string s, int pos, int len) {
    if (pos < 0 || pos >= s.length || pos + len - 1 >= s.length) return ERROR;
    if(ans.ch) free(ans.ch);
    ans.ch = (char*) malloc (len * sizeof(char));
    for(int i = 0; i < len; ++i) {
        ans.ch[i] = s.ch[pos + i];
    }
    ans.length = len;
    return OK;
}

//---------------kmp-------------------------------------

void get_next(string s, int next[]) {
    int len = s[0];
    next[1] = 0;
    int k = 0;
    int j = 1;
    while(j < len) {
        if(k == 0 || s[j] == s[k]) {
            ++k;    ++j;
            next[j] = k;
        }
        else {
            k = next[k];
        }
    }
}

int kmp_index(string s, string t, int pos) {
    int next[s[0] + 1];
    for(int i = 0; i < s[0]; ++i) next[i] = 0;
    get_next(s, next);
    int i = pos;    int j = 1;
    while (i <= s[0] && j <= t[0]) {
        if (j == 0 || s[i] == s[j]) {
            ++i;    ++j;
        }
        else 
            j = next[j];
    }
    if(j > t[0]) return i - t[0];
    return 0;
}

//------------------大概没问题，载体string有毛病----------------------------------
void test () {

}

int main () {
    test ();

    return 0;
}