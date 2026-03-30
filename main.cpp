#include <iostream>
#include <crtdbg.h>

#include "intersection.h"
#include "path-segment.h"
#include "traveller.h"
#include "navigation.h"


//The first two functions organize the nessecary steps for initializing path and traveller objects

std::shared_ptr<PathSegment> MakeAPath (intersection& firstintersect, intersection& secondintersect, char id) {

	std::shared_ptr<PathSegment> path = std::make_shared<PathSegment>(firstintersect, secondintersect, id);

	firstintersect.connectedPaths.push_back(path);
	secondintersect.connectedPaths.push_back(path);

	return path;

}


void MakeATraveller (PathSegment& on_path, const point& goal, const std::string& message) {

	//Make A Traveller defaults to trying to use the positive lane
	if (on_path.PositiveLane.CheckForSpace() == true) {

		on_path.PositiveLane.lane_queue.emplace_back(goal, message); 

		on_path.PositiveLane.lane_queue.back().MoveTo(on_path.GetLaneDestination(Direction::Positive)); //Travellers coordinate is updated for first frame might take out later
		
	}
	
	//If Positive is full, but Inverse is not, use the exact same code on the Inverse lane
	else if (on_path.InverseLane.CheckForSpace() == true) {

		on_path.InverseLane.lane_queue.emplace_back(goal, message);
		on_path.PositiveLane.lane_queue.back().MoveTo(on_path.GetLaneDestination(Direction::Positive)); 
	}

	//If both lanes are full, throw an error
	else {
		throw std::runtime_error("Could not add traveller on path because both lanes are full");
	}
	
}

int main() {
	
	//Creating a square intersection layout

	intersection p1 = intersection(0, 0);
	intersection p2 = intersection(0, 10);
	intersection p3 = intersection(10, 10);
	intersection p4 = intersection(10, 0);

	//Giving it PathSegments

	std::shared_ptr<PathSegment> Path_A = MakeAPath(p1, p2, 'a');
	std::shared_ptr <PathSegment> Path_B = MakeAPath(p2, p3, 'b');
	std::shared_ptr<PathSegment> Path_C = MakeAPath(p3, p4, 'c');
	std::shared_ptr<PathSegment> PAth_D = MakeAPath(p4, p1, 'd');


	MakeATraveller(*Path_A, p2, "Hello from Traveller A");

	//Process lane to see if Traveller can reach goal
	if (ProcessLane(Path_A, Direction::Positive) == true) {
		std::cout << "Success" << std::endl;
	}
	
	return 0;

};


