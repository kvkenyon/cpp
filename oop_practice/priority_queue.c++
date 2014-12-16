// -----------------
// PriorityQueue.c++
// -----------------

// http://www.cplusplus.com/reference/queue/priority_queue/

#include <algorithm>  // make_heap, pop_heap, push_heap
#include <cassert>    // assert
#include <deque>      // deque
#include <functional> // less
#include <iostream>   // cout, endl
#include <queue>      // priority_queue
#include <string>     // string
#include <vector>     // vector

template <typename T, typename C = std::deque<T>, typename P = std::less<T> >
class my_priority_queue {


public:
	typedef C container_type;
	typedef typename container_type::value_type value_type;
	typedef typename container_type::size_type size_type;

	typedef typename container_type::reference reference;
	typedef typename container_type::const_reference const_reference;

private:
	container_type _c; //container
	P _p; //predicate

public:

	friend bool operator == (const my_priority_queue& lhs, const my_priority_queue& rhs) {
		return lhs._c == rhs._c;
	}

	friend bool operator < (const my_priority_queue& lhs, const my_priority_queue& rhs) {
		return lhs._c < rhs._c;
	}

	my_priority_queue(P p = P(), const container_type& c = C())
		: _p(p), _c(c)
		{
			std::make_heap(_c.begin(), _c.end(), _p);
		}

	bool empty() const {
		return _c.empty();}

	size_type size() const {
		return _c.size();}

	void push(const T& v) {
		_c.push_back(v);
		std::push_heap(_c.begin(), _c.end(), _p);
	}

	void pop() {
		std::pop_heap(_c.begin(), _c.end(), _p);
		_c.pop_back();
	}

	const T& top() {
		return _c.front();
	}


};

template <typename C>
void priority_queues (
        const typename C::value_type& v1,
        const typename C::value_type& v2,
        const typename C::value_type& v3) {

    typedef typename C::container_type container_type;

    {
    C x;
    assert(x.empty());
    assert(x.size() == 0);
    x.push(v2);
    x.push(v3);
    x.push(v1);
    assert(!x.empty());
    assert(x.size() == 3);
    assert(x.top()  == v3);
    x.pop();
    assert(x.size() == 2);
    assert(x.top()  == v2);
    }

    {
    C x;
    x.push(v2);
    x.push(v3);
    x.push(v1);
//  x.top() = v2;                // doesn't compile
    }

    {
    C x;
    x.push(v2);
    x.push(v3);
    x.push(v1);
    C y(x);
//  assert(x == y);              // doesn't compile
    assert(!y.empty());
    assert(y.size() == 3);
    y.pop();
    assert(x.size() == 3);
    assert(x.top()  == v3);
    assert(y.size() == 2);
    assert(y.top()  == v2);
    }

    {
    std::less<std::string> x;
    container_type         y;
    y.push_back(v2);
    y.push_back(v3);
    y.push_back(v1);
    C z(x, y);
    z.pop();
    assert(y.size() == 3);
    assert(y.back() == v1);
    assert(z.size() == 2);
    assert(z.top()  == v2);
    }

    {
    C x;
    x.push(v2);
    x.push(v3);
    x.push(v1);
    C y;
    y.push(v3);
    y.push(v1);
    y = x;
    y.pop();
    assert(x.size() == 3);
    assert(x.top()  == v3);
    assert(y.size() == 2);
    assert(y.top()  == v2);
    }}

int main () {
    using namespace std;
    cout << "PriorityQueue.c++" << endl;

    priority_queues<    priority_queue<string>                                    >("abc", "def", "ghi");
    priority_queues<    priority_queue<string, std::deque<string> >               >("abc", "def", "ghi");
    priority_queues<    priority_queue<string, std::deque<string>, less<string> > >("abc", "def", "ghi");
//  priority_queues<    priority_queue<string, std::list<string>                > >("abc", "def", "ghi"); // doesn't compile

    priority_queues< my_priority_queue<string>                                    >("abc", "def", "ghi");
    priority_queues< my_priority_queue<string, std::deque<string>               > >("abc", "def", "ghi");
    priority_queues< my_priority_queue<string, std::deque<string>, less<string> > >("abc", "def", "ghi");
//  priority_queues< my_priority_queue<string, std::list<string>                > >("abc", "def", "ghi"); // doesn't compile

    cout << "Done." << endl;
    return 0;}