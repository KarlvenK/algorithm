#ifndef container_h
#define container_h

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

    template<typename T>
    class segment_tree{
        private:
            class node{
                public:
                    int l,r,m;
                    T sum,tag;
            };
        private:
            std::vector<T>* a;
            std::vector<node> seg_tr;
            int maxn;
        private:
            void build_tree(int rt,int l,int r){
                seg_tr[rt].l=l;
                seg_tr[rt].r=r;
                seg_tr[rt].m=(l+r)>>1;
                seg_tr[rt].tag=0;
                int mid=seg_tr[rt].m;
                if(l==r){
                    seg_tr[rt].sum=(*a)[l-1];
                    return;
                }
                build_tree(rt<<1,l,mid);
                build_tree(rt<<1|1,mid+1,r);
                push_up(rt);
                return;
            }
            void push_up(int rt){
                seg_tr[rt].sum=seg_tr[rt<<1].sum+seg_tr[rt<<1|1].sum;
                return;
            }
            void push_down(int rt,int m){
                if(seg_tr[rt].tag){
                    seg_tr[rt<<1].tag+=seg_tr[rt].tag;
                    seg_tr[rt<<1|1].tag+=seg_tr[rt].tag;
                    seg_tr[rt<<1].sum+=seg_tr[rt].tag*(m-(m>>1));
                    seg_tr[rt<<1|1].sum+=seg_tr[rt].tag*(m>>1);
                    seg_tr[rt].tag=0;
                }
            }
            void update(int rt,int l,int r,T val){
                if(seg_tr[rt].l==l && seg_tr[rt].r==r){
                    seg_tr[rt].tag+=val;
                    seg_tr[rt].sum+=val*(r-l+1);
                    return;
                }
                push_down(rt,seg_tr[rt].r-seg_tr[rt].l+1);
                if(r<=seg_tr[rt].m) update(rt<<1,l,r,val);
                else
                    if(l>seg_tr[rt].m) update(rt<<1|1,l,r,val);
                    else{
                        update(rt<<1,l,seg_tr[rt].m,val);
                        update(rt<<1|1,seg_tr[rt].m+1,r,val);
                    }
                push_up(rt);
            }
            T ask(int rt,int l,int r){
                if(seg_tr[rt].l==l && seg_tr[rt].r==r){
                    return seg_tr[rt].sum;
                }
                push_down(rt,seg_tr[rt].r-seg_tr[rt].l+1);
                T ret=0;
                if(r<=seg_tr[rt].m) ret+=ask(rt<<1,l,r);
                else
                    if(l>seg_tr[rt].m) ret+=ask(rt<<1|1,l,r);
                    else{
                        ret+=ask(rt<<1,l,seg_tr[rt].m);
                        ret+=ask(rt<<1|1,seg_tr[rt].m+1,r);
                    }
                return ret;
            }
        public:
            segment_tree()=default;
            segment_tree(std::vector<T>&arr):
            a(&arr),maxn(arr.size()){
                seg_tr.resize(maxn<<2+1);
                build_tree(1,1,maxn);
            }
        public:
            void add(int l,int r,T val){
                update(1,l+1,r+1,val);
            }
            T query(int l,int r){
                return ask(1,l+1,r+1);
            }          
    };
}
#endif
