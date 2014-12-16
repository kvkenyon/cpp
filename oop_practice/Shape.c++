class shape {

	friend bool operator < (const shape& lhs, const shape& rhs) {
		return ((lhs._x * lhs._y) < (rhs._x * rhs._y));}

	friend bool operator == (const shape& lhs, const shape& rhs) {
		return ((lhs._x * lhs._y) == (rhs._x * rhs._y));
	}

	friend std::ostream& operator << (std::ostream& out,const shape& lhs) {
		return out << lhs._x << " " << lhs._y << " " << (lhs._x * lhs._y);}

private:
	int _x;
	int _y;

public:
	shape(const int& x, const int& y)
		: _x(x), _y(y) 
		{}

	int area() {return 0;}

	void move(const int& x, const int& y) {
		_x = x;
		_y = y;}
};