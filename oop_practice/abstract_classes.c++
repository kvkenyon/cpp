
#include <iostream>
#include <cassert>

using namespace std;

class AbstractTetrapod {
	virtual void walk () = 0;
	virtual void see  () = 0;
	virtual void eat  () = 0;
	virtual void lives() = 0;
};

void AbstractTetrapod::walk() {
	cout << "Four-Legged Gait" << endl;
}

int main()
{
	
}