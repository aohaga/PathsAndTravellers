#include "navigation.h"

//Given a goal to get to, and a current intersection, determine which connected path segment will end closest to that goal by distance
std::shared_ptr<PathSegment> FindNearestEndingPath(const point &goal, const intersection &current_intersection) {

	std::shared_ptr<PathSegment> desired_path; //This will be the pointer to the PathSegment we want to go on
	
	float last_distance = INFINITY;

	for (std::shared_ptr<PathSegment> connected_path : current_intersection.connectedPaths) {

		intersection destination = connected_path->GetIntersectionOpposite(current_intersection);
		
		if (float d = destination.DistanceTo(goal) < last_distance) {

			last_distance = d;
			desired_path = connected_path;

		}
	}

	return desired_path;
}


//Returns true if a traveller was able to leave the lane queue, and false if not.
//ProcessLane takes a shared pointer to the PathSegment, with the desired directional lane in order to know what to process.
bool ProcessLane(std::shared_ptr<PathSegment> current_path, Direction lane_direction) {
	
	Lane& current_lane = current_path->GetLane(lane_direction);
	intersection& current_intersection = current_path->GetLaneDestination(lane_direction);
	Traveller& traveller = current_lane.lane_queue.front();

	
	if (traveller.GetGoal() == current_intersection) {
		
		std::cout << "Traveller reached its goal" << std::endl;
		std::cout << "Its message was "; traveller.PrintMessage();
		current_lane.lane_queue.pop_front();

		return true; //This returns true because the traveller was still able to leave the queue. 
		
	}

	else {

		//Find the next path
		std::shared_ptr<PathSegment> next_path = FindNearestEndingPath(traveller.GetGoal(), current_intersection);

		//Determine which lane to take
		Lane& next_lane = next_path->LaneFromDestination(traveller.GetGoal());

		if (next_lane.CheckForSpace() == true) {

			current_lane.Transfer(next_lane);
			next_lane.lane_queue.front().MoveTo(next_path->GetIntersectionOpposite(current_intersection));

			return true;

		}
		else {

			return false; //Traveller was unable to leave lane queue
		}
	}
	
}


