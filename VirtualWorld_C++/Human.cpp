#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "Human.h"
#include "World.h"
#include "Buttons.h"
#include "boardConsts.h"
using namespace boardConsts;
using namespace buttons;
using namespace humanStats;
Human::Human(int posX, int posY) {
	this->setAge(STARTING_AGE);
	this->setStrength(STRENGTH);
	this->setSymbol(SYMBOL);
	this->setMoveDist(MOVE_DIST);
	this->setInitiative(-1);
	this->setPos(posX, posY);
	this->state = -1;
}
Organism* Human::createChild(Point childPos) const {
	return nullptr;
}
void Human::action() {
	this->state = _getch();
	if (this->state == 0 || this->state == 0xE0) {
		this->state = _getch();
		Point next = this->getPos();
		this->setNextPos(this->getPos());
		switch (state) {
		case ARR_UP:
			next.move(0, -1, this->getMoveDist());
			break;
		case ARR_DOWN:
			next.move(0, 1, this->getMoveDist());
			break;
		case ARR_LEFT:
			next.move(-1, 0, this->getMoveDist());
			break;
		case ARR_RIGHT:
			next.move(1, 0, this->getMoveDist());
			break;
		}
		state = -1;
		this->setNextPos(next);
		if (this->getWorld()->getBoard()->isPointInBoundaries(this->getNextPos())) {
			if (this->getWorld()->getBoard()->getBoardField(this->getNextPos()) == nullptr)
				this->getWorld()->moveAnimalToNextPosition(this);
			else {
				this->getWorld()->getBoard()->getBoardField(this->getNextPos())->collision(this);
			}
		}
	}
}
void Human::Write(std::ostream& out) const {
	out << "a Human " << this->giveStats();
}
void Human::collision(Animal* invader) {
	Animal::collision(invader);
	//todo implement skill
}
Human::~Human() {

}