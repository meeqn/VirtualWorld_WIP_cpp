#pragma once
#include "Wolf.h"
using namespace wolfStats;
Wolf::Wolf(int posX, int posY) {
	this->setAnimal(INITIATIVE, STRENGTH, posX, posY, SYMBOL, MOVE_DIST);
}
void Wolf::Write(std::ostream& out) const {
	out << "a Wolf " << this->giveStats();
}
Organism* Wolf::createChild(Point childPos) const {
	Organism* animal = static_cast<Organism*>(new Wolf(childPos.x, childPos.y));
	return animal;
}
Wolf::~Wolf() {
}