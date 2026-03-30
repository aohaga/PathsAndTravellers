#include "intersection.h" 

float point::DistanceTo(const point &p) {
	double dx = static_cast<double>(x - p.x);
	double dy = static_cast<double>(y - p.y);
	return std::sqrt(dx * dx + dy * dy);
}

static point LerpByInterval(point a, point b, int interval) {
	point c;
	float t = 1 / interval;
	c.x = b.x * t + (1.0 - t) * a.x;
	c.y = b.y * t + (1.0 - t) * a.y;
	return c;
}

//Defining the equals operator
bool point:: operator==(const point & other) {
	return(x == other.x && y == other.y);
}

//Constructors
//With no arguements X and Y will revert automatically to {0,0}

point::point(float x, float y) :x{ x }, y{ y } {};
point::point() :x{ 0 }, y{ 0 } {};

intersection::intersection(float x, float y) :point(x, y) {};
intersection::intersection(point p) :point(p) {}; 
intersection::intersection() :point() {};
