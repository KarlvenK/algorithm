#pragma once
#include <iostream>
#include <algorithm>

namespace Karlven {
    template<typename T>
    class sharedPointer;

    template<typename T>
    auto swap (sharedPointer<T>& lhs, sharedPointer<T>& rhs) {
        using std::swap;
        swap(lhs.reference_count, rhs.reference_count);
        swap(lhs.ptr, rhs.ptr);
    }

    template<typename T>
    class sharedPointer {
    public:
        std::size_t* test() {
            return reference_count;
        }

        sharedPointer() : 
            ptr(nullptr), reference_count(new std::size_t(1)) { }

        explicit sharedPointer(T* raw_ptr) :
            ptr(raw_ptr), reference_count(new std::size_t(1)) { }

        sharedPointer(const sharedPointer& other) :
            ptr(other.ptr), reference_count(other.reference_count) {
                ++*reference_count;
            }

        sharedPointer(sharedPointer&& other) noexcept :
            ptr(other.ptr), reference_count(other.reference_count) {
                other.ptr = nullptr;
                other.reference_count = nullptr;
            }

        sharedPointer& operator=(const sharedPointer& rhs) {
            ++*reference_count;
            decrement_and_destroy();
            ptr = rhs.ptr;  reference_count = rhs.reference_count;
            return *this;
        }

        sharedPointer& operator=(const sharedPointer&& rhs) noexcept{
            Karlven::swap(*this, rhs);
            rhs.decrement_and_destroy();
            return *this;
        }

        operator bool() const{
            return ptr ? true : false;
        }

        T& operator *() const{
            return *ptr;
        }

        T* operator->() const{
            return &*ptr;
        }

        auto use_count() {
            return *reference_count;
        }

        auto get() const{
            return ptr;
        }

        auto unique() const{
            return *reference_count == 1;
        }
         
        auto swap(sharedPointer& rhs) {
            Karlven::swap(*this, rhs);
        }

        auto reset(T* pointer) {
            if (ptr != pointer) {
                decrement_and_destroy();
                ptr = pointer;
                reference_count = new std::size_t(1);
            }
        }
        ~sharedPointer() {
            decrement_and_destroy();
        }

    private:
        T* ptr;
        std::size_t* reference_count;

        auto decrement_and_destroy() {
            if (ptr && 0 == --reference_count) {
                delete reference_count;
                delete ptr;
            }
            else 
                if (!ptr) {
                    delete reference_count;
                }
            reference_count = nullptr;
            ptr = nullptr;
        }
    };
}
