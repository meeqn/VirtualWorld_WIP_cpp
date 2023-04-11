#include "Grass.h"

Grass::Grass(int posX, int posY) {
	this->setPlant(GRASS_STRENGTH, posX, posY, GRASS_SYMBOL);
}
Organism* Grass::createChild(Point childPos) const {
	Organism* animal = new Grass(childPos.x, childPos.y);;
	return animal;
}
void Grass::Write(std::ostream& out) const {
	std::cout << "a Grass ";
	this->giveStats();
}
Grass::~Grass() {
}