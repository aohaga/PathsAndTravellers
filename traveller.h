#pragma once
#include<iostream>
#include "intersection.h"

#define TRAVELLER_SCALE 1.5

//Travellers can move in two different directional lanes in a PathSegment
//This enum class helps keep things readable when it becomes nessecary to reference that feature.
enum class Direction{Positive, Inverse};

class Traveller {
	private:

		const float scale = TRAVELLER_SCALE; 
		point coordinate; //This is where the traveller is
		point goal;

		std::string Message;

	public:

		//Constructor takes a goal for the traveller to reach
		Traveller(point goal, std::string message);

		void PrintPosition(); //Prints the x and y values of coordinate
		void PrintMessage();

		point GetGoal();
		point GetCoordinate();
		void MoveTo(const intersection& new_coordinate);
		void MoveTo(point new_coordinate);
};