#pragma once
#include <memory>

namespace Karlven {
    template<typename T>
    class vec{
    public:
        vec() : element(nullptr), first_free(nullptr), cap(nullptr) { }
        vec(std::initializer_list<T> l);
        vec(const vec& v) {
            std::pair<T*, T*> new_data = alloc_n_copy(v.begin(), v.end());
            element = new_data.first;
            first_free = cap = new_data.second;
        }
        vec(const std::size_t n);
        vec(const std::size_t n, const T& c);

        ~vec();

        void push_back(const T& rhs);

        std::size_t size() const {
            return first_free - element;
        }
        std::size_t capacity() const {
            return cap - element;
        }
        T* begin() {
            return element;
        }
        T* end() {
            return first_free;
        }

        T operator [](int n) {
            return *(element + n);
        }

        void reserve(const std::size_t n);
        
        void resize(const std::size_t n);
        void resize(const std::size_t n, const T& t);

    private:
        T* element;
        T* first_free;
        T* cap;

        std::allocator<T> alloc;

        std::pair<T*, T*> alloc_n_copy(T* b, T* e) {
            T* data = alloc.allocate(e - b);
            return {data, std::uninitialized_copy(b, e, data)};
        }

        void wy_alloc_n_move(std::size_t n);
        void reallocate();
        void chk_n_alloc() {
            if (size() == capacity()) 
                reallocate();
        }

        void free();

    };

    template<typename T>
    void vec<T>::free() {
        if (element) {
            for (auto p = first_free; p != element;) 
                alloc.destroy(--p);
        }
        alloc.deallocate(element, capacity());
    }

    template<typename T>
    vec<T>::vec(const std::size_t n, const T& c) {
        T* newdata = alloc.allocate(n);
        T* p = newdata;
        for (p; p != newdata + n;)
            alloc.construct(p++, c);
        element = newdata;
        first_free = cap = newdata + n;
    }

    template<typename T>
    vec<T>::vec(std::initializer_list<T> l) {
        T* newdata = alloc.allocate(l.size());
        T* p = newdata;
        for (auto& t : l) 
            alloc.construct(p++, t);
        element = newdata;
        first_free = cap = element + l.size();
    }
    
    template<typename T>
    vec<T>::vec(std::size_t n) {
        T* newdata = alloc.allocate(n);
        T* p = newdata;
        for (p; p != newdata + n;)
            alloc.construct(p++, T());
        element = newdata;
        first_free = cap = newdata + n;
    }

    template<typename T>
    vec<T>::~vec() {
        free();
    }

    template<typename T>
    void vec<T>::resize(const std::size_t n) {
        resize(n, T());
    }
    
    template<typename T>
    void vec<T>::resize(const std::size_t n, const T& t) {
        if (n < size()) {
            for (auto p = element + n; p != first_free;)
                alloc.destroy(p++);
            first_free = element + n;
        }
        else
            if (n > size()) {
                for (auto i = size(); i != n; ++i) {
                    push_back(t);
                }
            }
    }

    template<typename T>
    void vec<T>::reserve(std::size_t n) {
        if (n <= capacity()) return;
        wy_alloc_n_move(n);
    }

    template<typename T>
    void vec<T>::wy_alloc_n_move(std::size_t n){
        std::size_t newcapacity = n;
        T* newdata = alloc.allocate(n);
        T* dest = newdata;
        T* old = element;

        for (std::size_t i = 0; i != size(); ++i) {
            alloc.construct(dest++, std::move(*old++));
        }

        free();
        element = newdata;
        first_free = dest;
        cap = element + newcapacity;
    }

    template<typename T>
    void vec<T>::reallocate() {
        std::size_t newcapacity = size() ? 2 * size() : 1;
        wy_alloc_n_move(newcapacity);
    }

    template<typename T>
    void vec<T>::push_back(const T& rhs) {
        chk_n_alloc();
        alloc.construct(first_free++, rhs);
    }
}
