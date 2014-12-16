


class A {
	int _a;
	static int _sa;

public:

	A(int a) : _a(a) {

	}

	struct B {
		int f() {
			return _sa;
		}
	};

private:
	struct C : A{


		int f() {
			return _a;
		}
	};
};

int main() {
	A a(2);

	A::B b;

	//A::C c;
}