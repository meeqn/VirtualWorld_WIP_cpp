#pragma once
#include <iostream>
#include "Point.h"
class Organism;

class Board {
#define DEFAULT_BOARD_SIZE_X 20
#define DEFAULT_BOARD_SIZE_Y 20
#define OUT_OF_BOUNDS -1
#define BLANK_MAP_SPACE '~'
private:
	const int sizeX, sizeY;
	Organism*** boardFields;

	Board();
	Board(int x, int y);
	void setBoardField(Point pos, Organism* val);
	void buildBoard();
	void deleteBoard();
	~Board();

	friend class World;
public:
	Organism* getBoardField(Point pos) const;
	bool isPointInBoundaries(Point pos) const;
};