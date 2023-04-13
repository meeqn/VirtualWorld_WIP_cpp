#include "Sheep.h"

Sheep::Sheep(int posX, int posY) {
	this->setAnimal(SHEEP_INITIATIVE, SHEEP_STRENGTH, posX, posY, SHEEP_SYMBOL, SHEEP_MOVE_DIST);
	//std::cout << "Created a Sheep ";
	//this->giveStats();
	//std::cout << "\n";
}
Organism* Sheep::createChild(Point childPos) const {
	Organism* animal = new Sheep(childPos.x, childPos.y);;
	return animal;
}
void Sheep::Write(std::ostream& out) const {
	out << "a Sheep " << this->giveStats();
}
Sheep::~Sheep() {
	std::cout << "Destroyed a Sheep ";
	this->giveStats();
	std::cout << "\n";
}