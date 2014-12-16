// ---------
// Queue.c++
// ---------

// http://www.cplusplus.com/reference/queue/queue/

#include <cassert>  // assert
#include <deque>    // deque
#include <iostream> // cout, endl
#include <list>     // list
#include <queue>    // queue 
#include <string>   // string
#include <utility>  // !=, <=, >, >=
#include <vector>   // vector

using namespace std::rel_ops;

template <typename T, typename C = std::deque<T> >
class my_queue {

	friend bool operator == (const my_queue& lhs, const my_queue& rhs) {
		return lhs._c == rhs._c;
	}

	friend bool operator < (const my_queue& lhs, const my_queue& rhs) {
		return lhs._c < rhs._c;
	}

public:

	typedef C container_type;

	typedef typename container_type::value_type value_type;
	typedef typename container_type::size_type size_type;

	typedef typename container_type::reference reference;
	typedef typename container_type::const_reference const_reference;

private:
	container_type _c;

public:

	my_queue(const container_type& c = C())
		: _c(c)
		{}

	reference front() {
		return _c.front();
	}

	const_reference front() const {
		return _c.front();
	}

	reference back() {
		return _c.back();
	}

	const_reference back() const {
		return _c.back();
	}

	void push(const value_type& v) {
		_c.push_back(v);
	}

	void pop() {
		_c.pop_front();
	}

	size_type size() const {
		return _c.size();
	}

	bool empty() const {
		return _c.empty();
	}
};

template <typename C>
void queues (
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
    assert(x.size()  == 3);
    assert(x.front() == v1);
    assert(x.back()  == v3);
    x.pop();
    assert(x.size()  == 2);
    assert(x.front() == v2);
    assert(x.back()  == v3);
    }

    {
    C x;
    x.push(v1);
    x.push(v2);
    x.push(v3);
    x.front() = v2;
    assert(x.front() == v2);
    x.back()  = v2;
    assert(x.back()  == v2);
    }

    {
    C x;
    x.push(v1);
    x.push(v2);
    x.push(v3);
    C y(x);
    assert(x == y);
    y.pop();
    assert(x.size()  == 3);
    assert(x.front() == v1);
    assert(x.back()  == v3);
    assert(y.size()  == 2);
    assert(y.front() == v2);
    assert(y.back()  == v3);
    }

    {
    container_type x;
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    C y(x);
    y.pop();
    assert(x.size()  == 3);
    assert(x.front() == v1);
    assert(x.back()  == v3);
    assert(y.size()  == 2);
    assert(y.front() == v2);
    assert(y.back()  == v3);
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
    assert(x.size()  == 3);
    assert(x.front() == v1);
    assert(x.back()  == v3);
    assert(y.size()  == 2);
    assert(y.front() == v2);
    assert(y.back()  == v3);
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
    cout << "Queue.c++" << endl;

    queues<    queue<string>                       >("abc", "def", "ghi");
    queues<    queue<string, std::list<string>   > >("abc", "def", "ghi");
//  queues<    queue<string, std::vector<string> > >("abc", "def", "ghi"); // doesn't compile

    queues< my_queue<string>                       >("abc", "def", "ghi");
    queues< my_queue<string, std::list<string>   > >("abc", "def", "ghi");
//  queues< my_queue<string, std::vector<string> > >("abc", "def", "ghi"); // doesn't compile

    cout << "Done." << endl;
    return 0;}