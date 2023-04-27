#include "Fox.h"
#include "World.h"
using namespace foxStats;
Fox::Fox(int posX, int posY) {
	this->setAnimal(INITIATIVE, STRENGTH, posX, posY, SYMBOL, MOVE_DIST);
}
Organism* Fox::createChild(Point childPos) const {
	Organism* animal = static_cast<Organism*>(new Fox(childPos.x, childPos.y));
	return animal;
}
void Fox::action() {
	this->setNextPos(this->getWorld()->getBoard()->generateRandomNeighboringPosition(true, this->getMoveDist(), this)); // <- fox looks until it finds free position

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
}