#pragma once
#include "Wolf.h"

Wolf::Wolf(int posX, int posY) {
	this->setAnimal(WOLF_INITIATIVE, WOLF_STRENGTH, posX, posY, WOLF_SYMBOL, WOLF_MOVE_DIST);

	//std::cout << "Created a Wolf ";
	//this->giveStats();
	//std::cout << "\n";
}
void Wolf::Write(std::ostream& out) const {
	out << "a Wolf " << this->giveStats();
}
Organism* Wolf::createChild(Point childPos) const {
	Organism* animal = new Wolf(childPos.x, childPos.y);
	return animal;
}
Wolf::~Wolf() {
	std::cout << "Destroyed a Wolf ";
	this->giveStats();
	std::cout << "\n";
}