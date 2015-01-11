// -------------------
// type_deduction1.c++
// -------------------


/*******************************
* Effective Modern C++ Chapter 1
********************************/

// includes
#include <iostream>
#include <cassert>
#include <typeinfo>
#include <exception>
#include <string>
#include <cstddef> // size_t
#include <array>

//Template Type Deduction

template<typename T>
std::string f1(T& param) {
	std::string t = typeid(param).name(); 
	t = (t == "i" ? "int" : t);
	std::cout << t << std::endl;
	return t;}

template<typename T>
std::string f1(const T& param) {
	std::string t = typeid(param).name(); 
	t = (t == "i" ? "const int" : t);
	std::cout << t << std::endl;
	return t;}

template<typename T>
std::string f2(const T& param) {
	std::string t = typeid(param).name(); 
	t = (t == "i" ? "const int" : t);
	std::cout << t << std::endl;
	return t;}

template<typename T>
std::string f3(T* param) {
	using namespace std;
	std::string t = typeid(param).name();
	if (t == "Pi")	t = "pointer-to-int"; else t = "pointer-to-const-int";
	cout << t << endl;
	return t;}

template<typename T>
std::string f4(T&& param) {
	std::string t = typeid(param).name(); 
	t = (t == "i" ? "int" : t);
	std::cout << t << std::endl;
	return t;
}

template<typename T>
std::string f5(T param) {
	std::string t = typeid(param).name(); 
	t = (t == "i" ? "int" : t);
	if (t == "PKc") t = "const-pointer-to-value";
	std::cout << t << std::endl;
	return t;
}

//Returns array size as a compile-time constant
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept {
	return N;
}

void someFunc(int a, double b) {
	std::cout << a + b << std::endl;}

int main()
{
	using namespace std;
	cout << "type_deduction1.c++" << endl << endl;


	{ // Case 1: param is a pointer/ref type, but not a universal reference
	 	int x = 17;
	 	const int cx = x;
	 	const int& rx = x;
	 	assert(f1(x) == "int");  // T is an int; param is an int&
	 	assert(f1(cx) == "const int"); // T is a const int; param is a const int&
	 	assert(f1(rx) == "const int"); // T is a const int; param is a const int&
	 								   // rx's reference-ness is ignored during type deduction.
	 	// We ignore the reference going in.
	 	// The overloaded version is not necessary other than for showing constness in assertion.
	 	// Passing a const type to a function taking a reference type preserves constness.
	 	// "..the constness of the object becomes part of the type deduced for T" (Meyer 12).
	 	cout << endl;
	}

	{
		int x = 42;
		const int cx = x;
		const int& rx = x;

		assert(f2(x) == "const int");  //No overloading; T -> int; param -> const int&
		assert(f2(cx) == "const int"); // T is int; param is const int&
		assert(f2(rx) == "const int"); // T is int; param is const int&
		cout << endl;
	}

	{
		int x = 42;
		const int* px = &x;
		const int* const cpx = &x;

		f3(&x);  // T is int; param is int*
		f3(px);  // T is const int; param is const int*
		f3(cpx); // T is const int; param is const int const*
		cout << endl;
	}

	{ // Case 2: ParamType is a Universal Reference (T&&)
		int x = 42;
		const int cx = x;
		const int& rx = x;

		f4(x);   // x is an lvalue; so T is an int&; param is an int&
		f4(cx);  // cx is an lvalue; so T is a const int&; param is a const int&
		f4(rx);  // rx is an lvalue; so T is a const int&; param is a const int&

		f4(42);  // 42 is an rvalue; so T is an int; param is a int&&
		cout << endl;
	}

	{ // Case 3: ParamType is Neither a Pointer nor a Reference
	  // Pass-by-Value
	  // if ref; ignore ref
	  // if after ignore ref object is const; ignore const; if volatile ignore that too
		int x = 42;
		const int cx = x;
		const int& rx = x;

		f5(x);  //both int
		f5(cx); //both int
		f5(rx); //both int

		//This makes sense because although the original object can't be modified a copy can be altered.
		cout << endl;
	}

	{
		const char* const ptr = "fun with pointers";
		f5(ptr); //constness of what ptr points to is preserved; the pointer is copied thus can be changed.
	}

	{
		char x[] = "hello donald tree";
		const char name[] = "J. P. Briggs";
		assert(sizeof(name) == 13);

		const char* ptrToName = name; // array-to-pointer decay
		assert(sizeof(ptrToName) != 13);
		assert(sizeof(ptrToName) == 8); // 64-bit address space

		f5(name); // pass argument of const char name[]
				  // But there are no functions with array parameters; they are pointers
				  // So all arrays are treated as pointers.
				  // T is const char*
		f1(name); // treated as array!
		f1(x);    //A18_c -> array size 18 of char

		// So if you have to pass an array to a function make that a template with ref type.
		cout << endl;
	}

	{
		int keyVals[] = {1,3,7,9,11,22,35};

		//int mappedVals[arraySize(keyVals)]; //Prefer std::array
		std::array<int, arraySize(keyVals)> mappedVals; //Nice! Compile-time constants change the game.

	}

	{ //Function Types can decay into function pointers.
		f5(someFunc); //Pass-by-val; param deduced as ptr-to-func
					  //type is void(*)(int, double)
		f1(someFunc); //Pass-by-ref; param deduced as ref-to-func
					  //type is void(&)(int,double)
	}

	 cout << endl << "Done." << endl;
}




