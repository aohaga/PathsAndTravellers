#include "traveller.h"

Traveller::Traveller(point goal, std::string message) :goal{ goal }, Message{ message } {};

void Traveller::PrintPosition() {
	std::cout << "{" << coordinate.x << "," << coordinate.y << "}" << std::endl;
}

void Traveller::PrintMessage() {
	std::cout << Message << std::endl;
}

point Traveller::GetCoordinate() {
	return coordinate;
}

point Traveller::GetGoal() {
	return goal;
}

void Traveller::MoveTo(point new_coordinate) {
	coordinate = new_coordinate;
}

void Traveller::MoveTo(const intersection& new_coordinate) {
	coordinate.x = new_coordinate.x;
	coordinate.y = new_coordinate.y;
}
