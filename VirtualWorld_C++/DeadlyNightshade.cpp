#include "DeadlyNightshade.h"
#include "World.h"

DeadlyNightshade::DeadlyNightshade(int posX, int posY) {
	this->setPlant(DEADLY_NIGHTSHADE_STRENGTH, posX, posY, DEADLY_NIGHTSHADE_SYMBOL);
}
Organism* DeadlyNightshade::createChild(Point childPos) const {
	Organism* child = new DeadlyNightshade(childPos.x, childPos.y);;
	return child;
}
void DeadlyNightshade::collision(Animal * invader) {
	this->getWorld()->sp->addKillMessage(this, invader);
	this->getWorld()->moveOrganismToGraveyard(this);
	this->getWorld()->moveOrganismToGraveyard(invader);
}
void DeadlyNightshade::Write(std::ostream& out) const {
	out << "a Deadly Nightshade " << this->giveStats();
}
DeadlyNightshade::~DeadlyNightshade() {
}