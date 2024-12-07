#pragma once
#include "util.h"


class Coordinate
{
private:
	float x;
	float y;
public:
	Coordinate(float xArgument = 0.0, float yArgument = 0.0) : x(xArgument), y(yArgument) {}

	friend ostream& operator<<(ostream& os, const Coordinate& coord);
};

