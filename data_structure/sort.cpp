#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

void swap(int& a, int& b) {
    int temp = a;
    a = b; b = temp;
}

void insert_sort (int num[], int len) {
    for(int i = 1; i < len; ++i) {
        int key = num[i];
        int j = i - 1;
        while(j >= 0 && num[j] > key) {
            num[j + 1] = num[j];
            --j;
        }
        num[j + 1] = key;
    }
}

void bianry_insert_sort (int num[], int len) {
    for(int i = 1; i < len; ++i) {
        int key = num[i];
        int left = 0, right = i;//二分找到第一个大于key的地方，[0, i),没有的话返回i
        while(left < right) {         
            int m = (left + right) >> 1;
            if(num[m] > key) right = m;
            else left = m + 1;
        }
        for(int j = i - 1; j >= left; --j) {
            num[j + 1] = num[j];
        }
        num[left] = key;
    }
}

void bubble_sort (int num[], int len) {
    for(int i = 0; i < len - 1; ++i) 
        for(int j = 0; j < len - 1; ++j) 
            if(num[j] > num[j + 1]) swap(num[j], num[j + 1]);
}

int select_min_num (int num[], int k, int len) {
    int ret = k; int _min = num[k];
    for(int i = k + 1; i < len; ++i) {
        if(_min > num[i]) {
            _min = num[i];
            ret = i;
        }
    }
    return ret;
}

void select_sort (int num[], int len) {
    for(int i = 0; i < len; ++i) {
        int j = select_min_num(num, i, len);
        if(i != j) swap(num[i], num[j]);
    }
}

void shell_insert (int num[], int len, int gap) {
    int temp, j;
    for(int i = gap; i < len; ++i) {
        temp = num[i];
        for(j = i - gap; j >= 0 && num[j] > temp; j -= gap) 
            num[j + gap] = num[j];
        num[j + gap] = temp;
    }
}

void shell_sort (int num[], int len) {
    for(int gap = len >> 1; gap > 0; gap >>= 1) {
        shell_insert(num, len, gap);
    }
}

int partition (int num[], int left, int right) {
    int pivot = num[left];
    while(left < right) {
        while(left < right && num[right] >= pivot)  --right;
        num[left] = num[right];
        while(left < right && num[left] <= pivot) ++left;
        num[right] = num[left];
    }    
    num[left] = pivot;
    return left;
}

void qsort(int num[], int left, int right) {
    if(left < right) {
        int loc = partition(num, left, right);
        qsort(num, left, loc - 1);
        qsort(num, loc + 1, right);
    }
}

void quicksort (int num[], int len) {
    qsort(num, 0, len - 1);
}

void merge(int num[], int s, int m, int t, int temp[]) {
    int i, j, k;
    for(i = s, j = m + 1, k = 0; k <= t - s; ++k) {
        if(i == m + 1) {
            temp[k] = num[j++];
            continue;
        }
        if(j == t + 1) {
            temp[k] = num[i++];
            continue;
        }
        if(num[i] < num[j]) {
            temp[k] = num[i++];
            continue;
        }
        temp[k] = num[j++];
    }
    for(i = s, j = 0; i <= t; ++i, ++j) {
        num[i] = temp[j];
    }
}

void msort(int num[], int s, int t, int temp[]) {
    if(s < t) {
        int m = (s + t) >> 1;
        msort(num, s, m, temp);
        msort(num, m + 1, t, temp);
        merge(num, s, m, t, temp);
    }
}
void merge_sort (int num[], int len) {
    int* temp = (int*) malloc(sizeof(int) * len);
    msort(num, 0, len - 1, temp);
    free(temp);
}

void heap_adjust (int num[], int s, int t) {
    int dad = s;
    int son = dad * 2 + 1;
    while(son <= t) {
        if(son + 1 <= t && num[son] < num[son + 1])
            ++son;
        if(num[dad] > num[son]) return;
        else {
            swap(num[dad], num[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heap_sort (int num[], int len) {
    for(int i = len >> 1 - 1; i >= 0; --i) 
        heap_adjust(num, i, len - 1);
    for(int i = len - 1; i > 0; --i) {  //由于是大根堆所以要倒序
        swap(num[0], num[i]);
        heap_adjust(num, 0, i - 1);
    }
}

int maxbit(int num[], int len) {
    int max_num = num[0];
    for(int i = 1; i < len; ++i) {
        if(max_num < num[i])
            max_num = num[i];
    }
    int d = 1;
    int p = 10;
    while(max_num >= p) {
        max_num /= 10;
        ++d;
    }
    return d;
}

void radix_sort (int num[], int len) {
    int d = maxbit(num, len);
    int* temp = (int*) malloc(sizeof(int) * len);
    int* count = (int*) malloc(sizeof(int) * 10);
    int radix = 1;
    for(int i = 1; i <= d; ++i) {
        for(int j = 0; j < 10; ++j) count[j] = 0;
        for(int j = 0; j < len; ++j) {
            int k = (num[j] / radix) % 10;
            count[k]++;
        }
        for(int j = 1; j < 10; ++j) 
            count[j] = count[j - 1] + count[j];
        for(int j = len - 1; j >= 0; --j) {
            int k = (num[j] / radix) % 10;
            temp[count[k] - 1] = num[j];
            count[k]--;
        }
        for(int j = 0; j < len; ++j) 
            num[j] = temp[j];
        radix *= 10;
    }   
    free(count);
    free(temp);
}

//--------------------

bool check (int num[], int len) {
    for(int i = 1; i < len; ++i) 
        if(num[i] < num[i - 1]) return false;
    return true;
}

void test() {
    int len = 50;
    int num[len];
    srand((unsigned)time(NULL));
    for(int i = 0; i < len; ++i) {
        num[i] = rand() % 1000;
    }
    
    //insert_sort(num, len);
    //bianry_insert_sort(num, len);
    //bubble_sort(num, len);
    //select_sort(num, len);
    //shell_sort(num, len);
    //quicksort(num, len);
    //merge_sort(num, len);
    //heap_sort(num, len);
    radix_sort(num, len);

    if(check(num, len)) 
        cout << "OK" << endl;
    else 
        cout << "NO， fuck you 凸#_#凸" << endl;

    for(int i = 0; i < len; ++i) 
        cout << num[i] << " ";
}

int main() {
    test();

    return 0;
}