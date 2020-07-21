#ifndef agrm
#define agrm

#include <vector>
#include <cmath>
#include <climits>
#include <cstdlib>

namespace Karlven{
    template<typename T>
    class binary_indexed_tree{//单点修改，区间求和
        private:
            size_t my_size;//segement from 1 to my_size
            std::vector<T> segment;
            inline T lowbit(T x){
                return x&(-x);
            }
            T sum(int index){
                ++index;
                T ans=T();
                while(index>0){
                    ans+=segment[index];
                    index-=lowbit(index);
                }
                return ans;
            }
        public:
            binary_indexed_tree()=default;
            binary_indexed_tree(size_t size):
                my_size(size){
                    segment.resize(size+1);
                }

            T size(){
                return my_size;
            }
            void clear(){
                std::vector<T>().swap(segment);
                my_size=0;
            }
            void add(int index,T val){
                ++index;
                while(index<=my_size){
                    segment[index]+=val;
                    index+=lowbit(index);
                }
            }
            T sum(int l,int r){
                return sum(r)-sum(l-1);
            }
    };

    template<class T,class F>
    auto lower_bound(T left,T right,F val){
        while(left<right){
            auto mid=left+(right-left)/2;
            if(*mid>=val){
                right=mid;
            }else{
                left=mid+1;
            }
        }
        return left;
    }

    template<class T,class F>
    auto upper_bound(T left,T right, F val){
        while(left<right){
            auto mid=left+(right-left)/2;
            if(*mid>val){
                right=mid;
            }else{
                left=mid+1;
            }
        }
        return left;
    }

    template<typename T>
    class max_heap{
        public:
            max_heap()=default;
            max_heap(int max):
                heap_size(0),heap_max(max){
                    my_heap.resize(max+1);
                }
        public:
            inline int count() const{
                return heap_size;
            }
            inline bool empty() const{
                return heap_size==0;
            }
            void push(T data){
                my_heap[++heap_size]=data;
                up(heap_size);
            }
            T top(){
                return my_heap[1];
            }
            void pop(){
                std::swap(my_heap[1],my_heap[heap_size]);
                heap_size--;
                down(1);
            }
        private:
            void up(int key){
                while(key>1 && my_heap[key]>my_heap[key>>1]){
                    std::swap(my_heap[key],my_heap[key>>1]);
                    key>>=1;
                }
            }
            void down(int key){
                while((key<<1)<=heap_size){
                    int child=key<<1;
                    if(child+1<=heap_size && my_heap[child+1]>my_heap[child]) ++child;
                    if(my_heap[key]<my_heap[child]) std::swap(my_heap[key],my_heap[child]);
                    key=child;
                }
            }
        private:
            int heap_size;
            int heap_max;
            std::vector<T>my_heap;
    };

    template<typename T>
    class min_heap{
         public:
            min_heap()=default;
            min_heap(int max):
                heap_size(0),heap_max(max){
                    heap.resize(max+1);
                }
            inline int count() const{
                return heap_size;
            }
            inline bool empty() const{
                return heap_size==0;
            }
            T top(){
                return heap[1];
            }
            void push(T data){
                heap[++heap_size]=data;
                up(heap_size);
            }
            void pop(){
                std::swap(heap[1],heap[heap_size]);
                --heap_size;
                down(1);
            }
        private:
            void up(int key){
                while(key>1 && heap[key>>1]>heap[key]){
                    std::swap(heap[key],heap[key>>1]);
                    key>>=1;
                }
            }
            void down(int key){
                while((key<<1)<=heap_size){
                    int child=key<<1;
                    if(child+1<=heap_size && heap[child]>heap[child+1]) ++child;
                    if(heap[key]>heap[child]) std::swap(heap[key],heap[child]);
                    key=child;
                }
            }
        private:
            int heap_size;
            int heap_max;
            std::vector<T>heap;
    };
}
#endif
