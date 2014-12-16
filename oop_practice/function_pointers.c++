#include <iostream>
#include <cassert>

using namespace std;

double sum(double lhs, double rhs) {
	return lhs + rhs;
}

double product(double lhs, double rhs) {
	return lhs * rhs;
}

double caller(double (*FuncPointer) (double, double), double lhs, double rhs) {
	return FuncPointer(lhs, rhs);
}

int main() {
	cout << "function_pointers.c++" << endl;

	{
		cout << "main() address: " << &main << endl;
		cout << "sum () address: " << &sum << endl;
		cout << "product() address: " << &product << endl;
	}

	{
		double (*SumPointer) (double, double);
		double (*ProductPointer) (double, double);

		SumPointer = sum;
		ProductPointer = product;

		assert (SumPointer(2,2) == sum(2,2));
		assert (ProductPointer(2,2) == product(2,2));
	}

	{
		double (*SumPointer) (double, double);
		double (*ProductPointer) (double, double);

		SumPointer = sum;
		ProductPointer = product;

		assert (caller(SumPointer,2,3) == 5);
		assert (caller(ProductPointer,2,3) == 6);

	}


	cout << "Done." << endl;
}

