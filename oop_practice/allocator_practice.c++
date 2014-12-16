#include <iostream>
#include <string>
#include <cstddef>
#include <algorithm>
#include <cassert>

template <typename T>
class my_allocator {
    public:
        my_allocator()
        {}

        void construct(T* p, const T& v) {

        }

        void destroy(T* p) {

        }

        T* allocate(size_t s) {
            return 0;
        }

        void deallocate(T* p) {

        }
};

template <typename T>
class my_allocator2 {
    public:
        my_allocator2(bool heap)
        {}

        void construct(T* p, const T& v) {

        }

        void destroy(T* p) {

        }

        T* allocate(size_t s) {
            return 0;
        }

        void deallocate(T* p) {

        }
};

template <typename T, typename A = std::allocator<T> >
class my_vector {
    
    public:
        typedef T value_type;
        typedef value_type* const pointer;
        typedef A allocator;
        typedef const size_t size;

    private:
        allocator _x;           // my allocator
        size _s; // my size
        pointer _a;     // point to my beginning

    public:
        my_vector(size_t s = 0, const value_type& v = value_type(), const A& x = A())
            : _s(s), _x(x), _a(_x.allocate(_s))
        {

        }
};

int main()
{
    {
        my_vector<int> x;
    }

    {
        my_vector<int, my_allocator<int> > x; 
    }

    {
        my_vector<int, my_allocator2<int> > x(0,0,my_allocator2<int>(true)); 
    }
}
