#pragma once
#include "traveller.h"
#include "intersection.h"

#include<memory>
#include<deque>
#include<iostream>
#include<cmath>;


enum signal { Go, Stop };

struct Lane {

	int traveller_maximum;

	std::deque<Traveller> lane_queue;
	
	bool CheckForSpace();

	void Transfer(Lane& to_lane);

};

class PathSegment {

	private:

		signal signal_state = Stop;

		intersection& intersectionA;
		intersection& intersectionB;

	public:

		char id;

		Lane PositiveLane;
		Lane InverseLane;

		//Constructor takes two intersections as end-points and a single character for an id
		PathSegment(intersection &endpoint_a, intersection &endpoint_b, char id);
		
		int GetMaximum();
		signal GetSignal();
		void ChangeSignal(signal newState);
		
		Lane& LaneFromDestination(const point &destination);
		Lane& GetLane(Direction dir);

		//Helpful functions for getting interesections based on context
		intersection& GetLaneOrigin(Direction dir);
		intersection& GetLaneDestination(Direction dir);
		intersection& GetIntersectionOpposite(const intersection& i);

};