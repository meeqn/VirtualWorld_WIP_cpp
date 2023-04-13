#include "Fox.h"
#include "World.h"

Fox::Fox(int posX, int posY) {
	this->setAnimal(FOX_INITIATIVE, FOX_STRENGTH, posX, posY, FOX_SYMBOL, FOX_MOVE_DIST);
}
Organism* Fox::createChild(Point childPos) const {
	Organism* animal = new Fox(childPos.x, childPos.y);;
	return animal;
}
void Fox::action() {
	this->setNextPos(this->getWorld()->getBoard()->generateRandomNeighboringPosition(false, this->getMoveDist(), this));

	Organism* nextFieldVal = this->getWorld()->getBoard()->getBoardField(this->getNextPos());
	if (nextFieldVal == nullptr)
		this->getWorld()->moveAnimalToNextPosition(this);
	else if(nextFieldVal->getSymbol()==this->getSymbol() || nextFieldVal->getStrength()<=this->getStrength()){
		nextFieldVal->collision(this);
	}
	this->deactivate();
}
void Fox::Write(std::ostream& out) const {
	out << "a Fox " << this->giveStats();
}
Fox::~Fox() {
	std::cout << "Destroyed a Fox ";
	this->giveStats();
	std::cout << "\n";
}