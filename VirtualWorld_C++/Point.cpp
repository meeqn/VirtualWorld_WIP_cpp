#include "Point.h"
Point::Point() : x(UNDEFINED), y(UNDEFINED) {};
Point::Point(int x, int y) : x(x), y(y) {};
bool Point::isUndefined() const{
	if (this->x == UNDEFINED || this->y == UNDEFINED) {
		return true;
	}
	else {
		return false;
	}
}
void Point::move(int paramX, int paramY, int moveRange){
	this->x += (moveRange * paramX);
	this->y += (moveRange * paramY);
}
Point::~Point() {
}