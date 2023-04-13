#include "Board.h"

void Board::buildBoard() {
	int height = this->sizeY;
	int width = this->sizeX;
	Organism*** newBoard = new Organism * *[height];

	for (int i = 0; i < height; i++)
		newBoard[i] = new Organism * [width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			newBoard[i][j] = nullptr;

	this->boardFields = newBoard;
}
void Board::deleteBoard() {
	int height = this->sizeY;

	for (int i = 0; i < height; i++)
		delete[] this->boardFields[i];

	delete[] this->boardFields;
}
void Board::setBoardField(Point pos, Organism* val) {
	this->boardFields[pos.y][pos.x] = val;
}
Organism* Board::getBoardField(Point pos) const {
	return this->boardFields[pos.y][pos.x];
}
bool Board::isPointInBoundaries(Point pos) const {
	if (pos.isUndefined())
		return false;
	else if (pos.x <= OUT_OF_BOUNDS || pos.y <= OUT_OF_BOUNDS)
		return false;
	else if (pos.x >= this->sizeX || pos.y >= this->sizeY)
		return false;
	else
		return true;
}

Point Board::generateRandomNeighboringPosition(const bool needFreePosition, int range, Organism *organism) const {
	int move;
	unsigned short control = 0b0000;
	Point newPos;
	do {
		move = rand() % DIRECTIONS_NUM;
		newPos.x = organism->getPos().x;
		newPos.y = organism->getPos().y;
		switch (move) {
		case directions::UP:
			newPos.move(0, -1, range);
			control = control | 0b1000;
			break;
		case directions::RIGHT:
			newPos.move(1, 0, range);
			control = control | 0b0100;
			break;
		case directions::DOWN:
			newPos.move(0, 1, range);
			control = control | 0b0010;
			break;
		case directions::LEFT:
			newPos.move(-1, 0, range);
			control = control | 0b0001;
			break;
		}
		if (control == 0b1111) {
			newPos.x = UNDEFINED;
			newPos.y = UNDEFINED;
			return newPos;
		}
	} while (!this->isPointInBoundaries(newPos) ||
		(needFreePosition == true && this->getBoardField(newPos) != nullptr));
	return newPos;
}
void Board::drawTheBoard() const {
	for (int i = 0; i < this->sizeY; i++) {
		for (int j = 0; j < this->sizeX; j++) {
			if (this->getBoardField(Point(j, i)) != nullptr)
				this->getBoardField(Point(j, i))->draw();
			else
				printf("%c", BLANK_MAP_SPACE);
		}
		printf("\n");
	}
}

Board::Board(): sizeX(DEFAULT_BOARD_SIZE_X), sizeY(DEFAULT_BOARD_SIZE_Y) {
	buildBoard();
}
Board::Board(int x, int y) : sizeX(x), sizeY(y) {
	buildBoard();
}
Board::~Board() {
	deleteBoard();
	std::cout << "Board memory freed"<<std::endl;
}
