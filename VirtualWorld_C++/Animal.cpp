#include "Animal.h"
#include "World.h"
#include "boardConsts.h"
using namespace boardConsts;
Point Animal::getNextPos() const {
	return this->nextPos;
}
int Animal::getMoveDist() const {
	return this->moveDist;
}

void Animal::setNextPos(Point newPos) {
	this->nextPos = newPos;
}
void Animal::setNextPos(int newPosX, int newPosY) {
	this->nextPos = Point(newPosX, newPosY);
}
void Animal::setMoveDist(int dist) {
	this->moveDist = dist;
}

void Animal::action() {
	this->setNextPos(this->getWorld()->getBoard()->generateRandomNeighboringPosition(false, this->getMoveDist(), this));

	Organism* nextFieldVal = this->getWorld()->getBoard()->getBoardField(this->getNextPos());
	if (nextFieldVal == nullptr)
		this->getWorld()->moveAnimalToNextPosition(this);
	else {
		nextFieldVal->collision(this);
	}
	this->deactivate();
}

void Animal::breed(Animal* secondAnimal) {
	Point childPos;
	childPos = this->getWorld()->getBoard()->generateRandomNeighboringPosition(true, 1, this);
	if (childPos.isUndefined())
		childPos = this->getWorld()->getBoard()->generateRandomNeighboringPosition(true, 1, secondAnimal);
	if (!childPos.isUndefined()) {
		Organism* offspring = createChild(childPos);
		this->getWorld()->addOrganismToWorldInactive(offspring);
		this->deactivate();//if organism is used for breeding, it loses it's turn (if it hasn't moved yet) to prevent board filling snowball

		this->getWorld()->sp->addBirthMessage(this, secondAnimal, dynamic_cast<Animal*>(offspring));
	}

}
void Animal::collision(Animal* invader) {

	if (invader->getSymbol() == this->getSymbol()) {
		this->breed(invader);
	}
	else
	{
		this->organismGetsAttacked(invader);
	}
}
void Animal::setAnimal(int initiative, int strength, int posX, int posY, char sym, int moveDist) {
	this->setAge(STARTING_AGE);
	this->setInitiative(initiative);
	this->setStrength(strength);
	this->setNextPos(OUT_OF_BOUNDS, OUT_OF_BOUNDS);
	this->setSymbol(sym);
	this->setPos(posX, posY);
	this->setMoveDist(moveDist);
	this->makeAlive();
}
Animal::~Animal() {
}