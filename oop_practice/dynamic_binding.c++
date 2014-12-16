#include <iostream>
#include <cassert>


class A {
	friend bool operator == (const A& lhs, const A& rhs) {
		return lhs.equals(rhs);
	}

	friend bool operator != (const A& lhs, const A& rhs) {
		return !(lhs.equals(rhs));
	}


protected:
	virtual bool equals(const A& rhs) const {
		std::cout << "Calling parent equals." << std::endl;
		return (_a == rhs._a) && (_b == rhs._b);
	}
	
private:
	int _a,_b;

public:
	A(int a, int b) : _a(a), _b(b) {}
};

class B : public A {
	int _r;

protected:
	virtual bool equals(const A& rhs) const {
		std::cout << "Calling childs equals." << std::endl;
		if (const B* const b = dynamic_cast<const B*>(&rhs)){
			return A::equals(rhs) && (b->_r == _r);
		}
		return false;
	}

public:
	B(const int& a, const int& b, const int& r) : A(a,b), _r(r) {}
};

int main() {
	{
		A x(1,2);
		A y(1,2);

		assert (x == y);
	}

	{
		B x(1,2,3);
		B y(1,2,5);

		assert( x != y);
	}

}