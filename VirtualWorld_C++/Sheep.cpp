#include "Sheep.h"
using namespace sheepStats;
Sheep::Sheep(int posX, int posY) {
	this->setAnimal(INITIATIVE, STRENGTH, posX, posY, SYMBOL, MOVE_DIST);
}
Organism* Sheep::createChild(Point childPos) const {
	Organism* animal = static_cast<Organism*>(new Sheep(childPos.x, childPos.y));
	return animal;
}
void Sheep::Write(std::ostream& out) const {
	out << "a Sheep " << this->giveStats();
}
Sheep::~Sheep() {
}