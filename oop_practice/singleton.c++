#include <iostream>
#include <cassert>

class Singleton1 {
    private:
        static Singleton1 x;

        Singleton1() {}
        Singleton1(const Singleton1& c);

    public:
        static Singleton1& getInstance()
        {
            return x;
        }

        void f() {
            using namespace std;
            cout << "Singleton1::f()" << endl;
        }
};

Singleton1 Singleton1::x;

class Singleton2 {
    static Singleton2* s;
    private:
        Singleton2() {}
        Singleton2(const Singleton2& c);
    public:
        static Singleton2& getInstance() {
            //Lazy Instantiation
            if (s == 0) {
                s = new Singleton2();
                return *s;
            }
            return *s;
        }

        void f() {
            using namespace std;
            cout << "Singleton2::f()" << endl;
        }
};

Singleton2* Singleton2::s;


class Singleton3 {
    private:
        Singleton3() {}
        Singleton3(const Singleton3& c);

    public:

        static Singleton3& getInstance() {
            static Singleton3 x;
            return x;
        }

        void f() {
            using namespace std;
            cout << "Singleton3::f()" << endl;
        }
};


int main() {
    Singleton1::getInstance().f();
    Singleton2::getInstance().f();
    Singleton3::getInstance().f();

    assert(&Singleton1::getInstance() == &Singleton1::getInstance());
    assert(&Singleton2::getInstance() == &Singleton2::getInstance());
    assert(&Singleton3::getInstance() == &Singleton3::getInstance());
}
