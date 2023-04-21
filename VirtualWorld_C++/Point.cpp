#include "Point.h"
#include "boardConsts.h"
using namespace boardConsts;
Point::Point() : x(UNDEFINED_FIELD), y(UNDEFINED_FIELD) {};
Point::Point(int x, int y) : x(x), y(y) {};
bool Point::isUndefined() const{
	if (this->x == UNDEFINED_FIELD || this->y == UNDEFINED_FIELD) {
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