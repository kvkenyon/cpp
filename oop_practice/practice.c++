#include <iostream>

struct A {
    private:
        const int& _a;

    public:
        A(const int& a) : _a(a)
        {}

};

class B {
    const int& _x;

    public:
        B(const int& x) : _x(x)
        {}
};

class C {
    public:
        C() {}
};


class my_vector : B {
    const int _cx;
    const int& _x;
    A _a;
    C _c;

    public:
        my_vector(const int& x) : _x(x), B(x), _a(A(x)), _cx(x)
        {
           // _x = x; Not possible

        }
};

template <typename T>
class vector {
    private:
        int _s;
        std::allocator<T> _a;
        T* _p;

    public:
        vector(const int& s = 0, T& v = T()) :
            _a(),
            _s(s),
            _p(_a.allocate(s))
        {
            for (int i = 0; i != s; ++i) {
                _a.construct(_p + i, v);}
        }

        ~vector() {
            for (int i = 0; i != _s; ++i) {
                _a.destroy(_p + i);}
            _a.deallocate(_p);
        }

        T& operator [] (const int& i) {
            return *(_p + i);}

        const T& operator [] (size_t i) const {
            return (*const_cast<vector<T>*>(this))[i];}};


int main() {
    //B x; -- Can't because default constructor is lost
}

