#pragma once

#include <memory.h>

namespace Karlven {

    template<int _dim>
    struct array_size {
        int size;
        int total;
        array_size<_dim - 1> remains;

        array_size(int _size, const array_size<_dim - 1>& _remains) :
            size(_size),    total(_size * _remains.total),
            remains(_remains)
            { }
        
        array_size<_dim + 1> operator, (int new_size) {
            return array_size<_dim + 1>(size, (remains, new_size)); 
        }
    };

    template<>
    struct array_size<0> {
        int total;
        array_size() : total(1) { }

        array_size<1> operator, (int new_size) {
            return array_size<1>(new_size, array_size<0>());
        }
    };

    typedef array_size<0> array_sizes;  // important part. we use it to start the building 

    //-----------------------------------------------------------------------------------
    
    template<typename T, int _dim>
    class array_ref {
    private:
        const array_size<_dim>& sizes;
        T* data;
    public:
        array_ref(const array_size<_dim>& _sizes, T* _data) :
            sizes(_sizes), data(_data) { }
        array_ref<T, _dim - 1> operator[](int index) {
            return array_ref<T, _dim - 1> (sizes.remains, data + (index * sizes.remains.size));
        }

        int size() {
            return sizes.size;
        }

        int total_size() {
            return sizes.total;
        }
    };

    template<typename T>
    class array_ref<T, 1> {
    private:
        const array_size<1>& sizes;
        T* data;
    public:
        array_ref(const array_size<1>& _sizes, T* _data) :
            sizes(_sizes), data(_data) { }
        T& operator[](int index) {
            return data[index];
        }
        int size() {
            return sizes.size;
        }
        int total_size() {
            return sizes.total;
        }
    };

    //--------------------------------------------------------

    template<typename T, int _dim>
    class array {
    private:
        array_size<_dim> sizes;
        T* data;
    public:
        array(const array_size<_dim>& _sizes) :
            sizes(_sizes), data(new T[_sizes.total]) { }
        
        array(const array<T, _dim>& arr) :
            sizes(arr.sizes), data(new T[sizes.total]) {
                for (int i = 0; i < sizes.total; ++i) 
                    data[i] = arr.data[i];
            }
        
        array(array<T, _dim>&& arr) :
            sizes(arr.sizes), data(arr.data) {
                arr.data = nullptr;        //-----change 0  to  nullptr------------
            }

        ~array() {
            if (data) {
                delete[] data;
            }
        }

        array_ref<T, _dim> ref() {
            return array_ref<T, _dim>(sizes, data);
        }

        int size() {
            return sizes.size;
        }

        int total_size() {
            return sizes.total;
        }
        auto operator[](int index) {
            return ref()[index];
        }
    };
}