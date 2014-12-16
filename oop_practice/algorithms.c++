#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <cassert>
#include <utility>

#include "Shape.c++"

using namespace std::rel_ops;

template <typename T, typename II>
II quick_sort(II b, II e) {
	using namespace std;
	int size = std::distance(b,e);

	cout << "size: " << size << endl;

	if (size <= 4) {
		std::sort(b,e);
		return e;}

	int s = rand() % (size);

	cout << "offset: " << s << endl;

	cout << "begin: " << *b << endl;

	II splitter = b + s;

	cout << "splitter: " << *splitter << endl;

    cout << "end: " << *e << endl;

	std::vector<T> l, r; // Left and right
	II p = b;

	while(p != e) {
		if (*p <= *splitter)
			l.push_back(*p);
		else
			r.push_back(*p);
		++p;}

	II bl = l.begin();
	II el = quick_sort<T>(l.begin(), l.end());

	II br = r.begin();
	II er = quick_sort<T>(r.begin(), r.end());

	while (bl != el) {
		*b = *bl;
		++b;
		++bl;
	}

	while (br != er) {
		*b = *br;
		++b;
		++br;
	}

	assert(b == e);
	return e;
}


template <typename II>
void print(II b, II e, std::ostream& out) {
	using namespace std;
	while (b != e) {
		out << *b << endl;
		++b;
	}
}


int main() {

	using namespace std;

	{
		std::vector<int> u;

		for (int i = 0; i < 1000000; ++i) {
			u.push_back(rand() % 1000000);
		}

		quick_sort<int>(u.begin(), u.end());
		print(u.begin(), u.end(), cout);
	}

}
