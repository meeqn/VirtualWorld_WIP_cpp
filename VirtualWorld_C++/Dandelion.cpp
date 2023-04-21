#include "Dandelion.h"
#include "World.h"
using namespace dandelionStats;

Dandelion::Dandelion(int posX, int posY) {
	this->setPlant(STRENGTH, posX, posY, SYMBOL);
}
Organism* Dandelion::createChild(Point childPos) const {
	Organism* child = static_cast<Organism*>(new Dandelion(childPos.x, childPos.y));
	return child;
}
void Dandelion::action() {
	for (int i = 0; i < 3; i++) {
		Plant::action();
	}
}
void Dandelion::Write(std::ostream& out) const {
	out << "a Dandelion " << this->giveStats();
}
Dandelion::~Dandelion() {
}