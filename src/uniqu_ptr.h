#pragma once
//#include <algorithm>
#include "debugDelete.h"

namespace Karlven {
    template<typename, typename> class uniquePointer;
    template<typename T, typename D>
    void swap(uniquePointer<T,D>& lhs, uniquePointer<T,D>& rhs);
    
    template<typename T,typename D = DebugDelete>
    class uniquePointer {
        friend void swap<T,D>(uniquePointer<T,D>& lhs, uniquePointer<T,D>& rhs);
    public:
        uniquePointer(const uniquePointer& ) = delete;
        uniquePointer& operator = (const uniquePointer& ) = delete;
        uniquePointer() = default;
        explicit uniquePointer(T* p) :
            ptr(p) { }
        uniquePointer(uniquePointer<T, D>&& p) noexcept :
            ptr(p.ptr) {
                p.ptr = nullptr;
            }
        uniquePointer& operator = (uniquePointer<T, D>&& rhs) noexcept;
        uniquePointer& operator = (std::nullptr_t n) noexcept {
            if (n == nullptr) {
                deleter(ptr);
                ptr = nullptr;
            }
            return *this;
        }

        T& operator*() const {
            return *ptr;
        }
        T* operator->() const {
            return &*ptr;
        }

        T* get() const {
            return ptr;
        }

        void reset() {
            deleter(ptr);
            ptr = nullptr;
        }
        void reset(T* p) {
            deleter(ptr);
            ptr = p;
        }
        T* release();

        ~uniquePointer() {
            deleter(ptr);
        }
        
    private:
        T* ptr;
        D deleter;
    };

    template<typename T, typename D>    
    inline uniquePointer<T, D>& 
    uniquePointer<T,D>::operator = (uniquePointer<T, D>&& rhs) noexcept {
        if (this->ptr != rhs.ptr) {
            deleter(ptr);
            ptr = nullptr;
            Karlven::swap(*this, rhs);
        }
        return *this;
    }
 
    template<typename T, typename D>
    inline void swap(uniquePointer<T, D>& lhs, uniquePointer<T, D>& rhs) {
        using std::swap;
        swap(lhs.ptr, rhs.ptr);
        swap(lhs.deleter, rhs.deleter);
    }
    template<typename T, typename D>
    inline T* uniquePointer<T, D>::release() {
        T* ret = ptr;
        ptr = nullptr;
        return ret;
    }
}