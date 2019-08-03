//#include "aggregator.h"
#include "aggregator_t.h"

#include <iostream>

class Point
{
	double _x;
	double _y;

	friend std::ostream& operator << (std::ostream& o, const Point& p);
	friend constexpr Point normalize(int weight1, Point p1, int weight2, Point p2);
public:
	constexpr Point(double x, double y) : _x(x), _y(y) {}
};

std::ostream& operator << (std::ostream& o, const Point& p)
{
	return o << '(' << p._x << ',' << p._y << ')';
}

constexpr Point normalize(int weight1, Point p1, int weight2, Point p2)
{
	return Point((weight1*p1._x + weight2 * p2._x) / (weight1 + weight2), (weight1*p1._y + weight2 * p2._y) / (weight1 + weight2));
}

int main()
{
	constexpr Point p(1, 2);

	std::cout << p << '\n';

	constexpr Point p2(2, 3);
	constexpr Aggregator a( p );
	constexpr auto res = (a +p2);
	constexpr auto res2 = res / 2;

	std::cout << res2.get() << '\n';
}
