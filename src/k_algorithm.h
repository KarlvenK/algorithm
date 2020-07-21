#ifndef agrm
#define agrm

#include <vector>
#include <cmath>
#include <climits>
#include <cstdlib>

namespace Karlven{
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