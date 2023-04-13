#pragma once
#include <iostream>
#include "Point.h"
#include "Organism.h"
#define DEFAULT_BOARD_SIZE_X 20
#define DEFAULT_BOARD_SIZE_Y 20
#define OUT_OF_BOUNDS -1
#define BLANK_MAP_SPACE '~'
#define DIRECTIONS_NUM 4
class Board {
enum directions { UP, RIGHT, DOWN, LEFT };
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
	Point generateRandomNeighboringPosition(const bool needFreePosition, int range, Organism* organism) const;
	void drawTheBoard() const;
	bool isPointInBoundaries(Point pos) const;
};