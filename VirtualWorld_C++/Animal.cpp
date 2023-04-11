#include "Animal.h"
#include "World.h"
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
	this->setNextPos(this->generateNeighboringPositions(false, this->getMoveDist()));

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
	childPos = this->generateNeighboringPositions(true, 1);
	if (childPos.isUndefined())
		childPos = secondAnimal->generateNeighboringPositions(true, 1);
	if (!childPos.isUndefined()) {
		Organism* offspring = createChild(childPos);
		this->getWorld()->addOrganismToWorldInactive(offspring);
		std::cout << *offspring << " was born to " << *this << " and " << *secondAnimal << "\n";
		this->deactivate();//if organism is used for breeding, it loses it's turn (if it hasn't moved yet) to prevent board filling snowball
	}

}
void Animal::animalGetsAttacked(Animal * invader) {
	World* world = this->getWorld();
	if (this->getStrength() < invader->getStrength()) { //attacked and loses fight
		world->moveOrganismToGraveyard(this);
		world->moveAnimalToNextPosition(invader);
		std::cout << *invader << " killed " << *this << "\n";
	}
	else { //defends itself
		world->moveOrganismToGraveyard(invader);
		std::cout << *this << " killed " << *invader << "\n";
	}
}
void Animal::collision(Animal* invader) {

	if (invader->getSymbol() == this->getSymbol()) {
		this->breed(invader);
	}
	else
	{
		this->animalGetsAttacked(invader);
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