#include "Point.h"
Point::Point() {
	this->x = UNDEFINED;
	this->y = UNDEFINED;
}
Point::Point(int x, int y) {
	this->y = y;
	this->x = x;
}
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