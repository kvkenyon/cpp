// ---------
// stack.c++
// ---------

// http://www.cplusplus.com/reference/stack/stack/

#include <cassert>  // assert
#include <deque>    // deque
#include <iostream> // cout, endl
#include <list>     // list
#include <stack>    // stack
#include <string>   // string
#include <utility>  // !=, <=, >, >=
#include <vector>   // vector

using namespace std::rel_ops;

template <typename T, typename C = std::deque<T> >
class my_stack {

	friend bool operator == (const my_stack& lhs, const my_stack& rhs) {
		return (lhs._c == rhs._c);}

	friend bool operator < (const my_stack& lhs, const my_stack& rhs) {
		return (lhs._c < rhs._c);}

public:
	typedef T value_type;

	typedef T* pointer;
	typedef const T* const_pointer;

	typedef T& reference;
	typedef const T& const_reference;

	typedef C container_type;

private:
	container_type _c;

public:
	explicit my_stack(const container_type& c = container_type())
		: _c(c)
		{}

	bool empty() const {
		return _c.empty();}

	size_t size() const {
		return _c.size();}

	reference top() {
		return _c.back();}

	const_reference top() const {
		return _c.back();} 

	void pop() {
		_c.pop_back();}

	void push(const_reference vc) {
		_c.push_back(vc);
	}

};

template <typename C>
void stacks (
        const typename C::value_type& v1,
        const typename C::value_type& v2,
        const typename C::value_type& v3) {

    typedef typename C::container_type container_type;

    {
    C x;
    assert(x.empty());
    assert(x.size() == 0);
    x.push(v1);
    x.push(v2);
    x.push(v3);
    assert(!x.empty());
    assert(x.size() == 3);
    assert(x.top()  == v3);
    x.pop();
    assert(x.size() == 2);
    assert(x.top()  == v2);
    }

    {
    C x;
    x.push(v1);
    x.push(v2);
    x.push(v3);
    x.top() = v2;
    assert(x.top() == v2);
    }

    {
    C x;
    x.push(v1);
    x.push(v2);
    x.push(v3);
    C y(x);
    assert(x == y);
    y.pop();
    assert(x.size() == 3);
    assert(x.top()  == v3);
    assert(y.size() == 2);
    assert(y.top()  == v2);
    }

    {
    container_type x;
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    C y(x);
    y.pop();
    assert(x.size() == 3);
    assert(x.back() == v3);
    assert(y.size() == 2);
    assert(y.top()  == v2);
    }

    {
    C x;
    x.push(v1);
    x.push(v2);
    x.push(v3);
    C y;
    y.push(v3);
    y.push(v1);
    y = x;
    assert(x == y);
    y.pop();
    assert(x.size() == 3);
    assert(x.top()  == v3);
    assert(y.size() == 2);
    assert(y.top()  == v2);
    }

    {
    C x;
    x.push(v1);
    x.push(v2);
    x.push(v3);
    C y;
    y.push(v1);
    y.push(v2);
    y.push(v3);
    assert(x == y);
    assert(x <= y);
    assert(x >= y);
    assert(!(x != y));
    assert(!(x <  y));
    assert(!(x >  y));
    }}

int main () {
    using namespace std;
    cout << "Stack.c++" << endl;

    stacks<    stack<string>                       >("abc", "def", "ghi");
    stacks<    stack<string, std::list<string>   > >("abc", "def", "ghi");
    stacks<    stack<string, std::vector<string> > >("abc", "def", "ghi");

    stacks< my_stack<string>                       >("abc", "def", "ghi");
    stacks< my_stack<string, std::list<string>   > >("abc", "def", "ghi");
    stacks< my_stack<string, std::vector<string> > >("abc", "def", "ghi");

    cout << "Done." << endl;
    return 0;}