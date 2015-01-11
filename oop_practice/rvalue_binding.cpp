// ------------------
// rvalue_binding.c++
// ------------------

#include <iostream>
#include <cassert>
#include <string>

class A {
    int _a;
    
    public:
        
        A() : _a(0) 
            {}
            
        //Copy Constructor
        // Same as: A(const A& other)
        A(A const& other) {
         this->_a = other._a;}
    
        int getter() const {
            return _a;}
            
        void setter(const int& a) {
            _a = a;}
};

int main()
{
    using namespace std;
    
    cout << "rvalue_binding.c++" << endl;

    {
        std::string s1 = "test";

        //std::string&& r1 = s1; //error: can't bind to lvalue

        const std::string& r2 = s1;
        assert(r2 == s1);

        std::string& r3 = s1;
        std::string&& r4 = s1 + s1;

        assert((r3+r3) == r4);
    }
    
    //A& a = A(); doesn't compile
    
    {
        const A& ac = A();
        //ac.setter(99); doesn't compile
        assert(ac.getter() == 0);
    }
    
    {
        A&& a = A();
        a.setter(99);
        assert(a.getter() == 99);
    }
    cout << "Done." << endl;
}
