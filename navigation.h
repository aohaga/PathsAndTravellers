#pragma once

#include "intersection.h"
#include "path-segment.h"
#include "traveller.h"

//Navigation logic used to move travellers

bool ProcessLane(std::shared_ptr<PathSegment> current_path, Direction dir);


std::shared_ptr<PathSegment> FindNearestEndingPath(const point& goal, const intersection& current_intersection);

