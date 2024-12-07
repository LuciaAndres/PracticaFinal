#include "Coordinate.h"

ostream& operator<<(ostream& os, const Coordinate& coord)
{
	os << "(" << coord.x << ", " << coord.y << ")";
	return os;
}