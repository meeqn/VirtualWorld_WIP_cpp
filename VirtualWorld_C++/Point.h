#pragma once
#define UNDEFINED -1
struct Point
{
public:
	Point();
	Point(int x, int y);
	int x;
	int y;
	void move(int paramX, int paramY, int moveRange);
	bool isUndefined() const;
	~Point();
};
