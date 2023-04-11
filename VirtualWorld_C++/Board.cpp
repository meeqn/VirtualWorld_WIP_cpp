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
