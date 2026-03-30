#include "path-segment.h"

//Begin Lane Definitions

bool Lane::CheckForSpace() {
	if (lane_queue.size() < traveller_maximum) { return true; }
	else { return false; }
}

void Lane::Transfer(Lane& to_lane) {
	to_lane.lane_queue.emplace_back(lane_queue.front());
	lane_queue.pop_front();
}

//Begin Path Segment Definitions

//Constructor
PathSegment::PathSegment(intersection& endpoint_a, intersection& endpoint_b, char id) 
	: intersectionA{ endpoint_a }, intersectionB{ endpoint_b }, id{ id }
{
	//set how many travellers can fit in a lane, by dividing path length by traveller scale and rounding down
	int max = std::floor(intersectionA.DistanceTo(intersectionB) / TRAVELLER_SCALE);

	PositiveLane.traveller_maximum = max;
	InverseLane.traveller_maximum = max;

}

//Given an intersection, returns the lane of this PathSegment which moves towards it
Lane& PathSegment::LaneFromDestination(const point& destination) {
	if (intersectionB.x == destination.x && intersectionB.y == destination.y) {
		return PositiveLane;
	}
	else if (intersectionA == destination && intersectionA == destination) {
		return InverseLane;
	}
	else {
		throw std::runtime_error("DetermineLane could not match the intersection passed to it with one of the intersections of the path it was called on");
	}
}

//Get the lane which moves in the given direction. 
Lane& PathSegment::GetLane(Direction dir) {
	switch (dir) {
		case Direction::Positive:
			return PositiveLane;
			break;
		case Direction::Inverse:
			return InverseLane;
			break;
	}
}

//Returns the intersection considered the 'origin' by the lane of the given direction
intersection& PathSegment::GetLaneOrigin(Direction dir) {
	switch (dir) {
		case Direction::Positive:
			return intersectionA;
			break;
		case Direction::Inverse:
			return intersectionB;
			break;
	}
}

//Returns the intersection considered the 'destination' by the lane of given direction
intersection& PathSegment::GetLaneDestination(Direction dir) {
	switch (dir) {
	case Direction::Positive:
		return intersectionB;
		break;
	case Direction::Inverse:
		return intersectionA;
		break;
	}
}

//Returns the intersection opposite the one passed to this function
intersection& PathSegment::GetIntersectionOpposite(const intersection& i) {
	if (intersectionB == i) {
		return intersectionA;
	}
	else if (intersectionA == i) {
		return intersectionB;
	}
	else {
		throw std::runtime_error("GetIntersectionOpposite could not match the intersection passed to it with one of the intersections of the path it was called on");
	}
}

signal PathSegment::GetSignal() {
	return signal_state;
}

void PathSegment::ChangeSignal(signal newstate) {
	signal_state = newstate;
}

int PathSegment::GetMaximum() { 
	return PositiveLane.traveller_maximum; 
	// shouldnt matter what lane we return, the maximum should be the same for both
}


