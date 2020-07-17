#ifndef agrm
#define agrm

#include <vector>
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
}
#endif