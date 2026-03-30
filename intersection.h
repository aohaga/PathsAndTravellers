#pragma once
#include<vector>
#include<cmath>
#include<memory>

struct point {
	float x;
	float y;

	float DistanceTo(const point& p);

	//Constructors
	point(float x, float y);
	point();

	//Defining equals
	bool operator==(const point& other);

};

class PathSegment; // Forward declaration of PathSegment class. There is a circular dependcy between PathSegment and intersection that is resolved this way

//A point which additionally stores a std::vector of all the PathSegments connected to it.
struct intersection : point {

	std::vector<std::shared_ptr<PathSegment>>connectedPaths;

	//Constructors
	intersection(float x, float y);
	intersection(point p);
	intersection();

};

static point LerpByInterval(point a, point b, int interval);
