#include "Dandelion.h"
#include "World.h"

Dandelion::Dandelion(int posX, int posY) {
	this->setPlant(DANDELION_STRENGTH, posX, posY, DANDELION_SYMBOL);
}
Organism* Dandelion::createChild(Point childPos) const {
	Organism* child = new Dandelion(childPos.x, childPos.y);;
	return child;
}
void Dandelion::action() {
	for (int i = 0; i < 3; i++) {
		Plant::action();
	}
}
void Dandelion::Write(std::ostream& out) const {
	std::cout << "a Dandelion ";
	this->giveStats();
}
Dandelion::~Dandelion() {
}