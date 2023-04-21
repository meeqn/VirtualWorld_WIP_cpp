#include "Grass.h"
using namespace grassStats;
Grass::Grass(int posX, int posY) {
	this->setPlant(STRENGTH, posX, posY, SYMBOL);
}
Organism* Grass::createChild(Point childPos) const {
	Organism* child = static_cast<Organism*>(new Grass(childPos.x, childPos.y));
	return child;
}
void Grass::Write(std::ostream& out) const {
	out << "a Grass " << this->giveStats();
}
Grass::~Grass() {
}