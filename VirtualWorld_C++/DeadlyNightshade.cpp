#include "DeadlyNightshade.h"
#include "World.h"

using namespace deadlyNightshadeStats;

DeadlyNightshade::DeadlyNightshade(int posX, int posY) {
	this->setPlant(STRENGTH, posX, posY, SYMBOL);
}
Organism* DeadlyNightshade::createChild(Point childPos) const {
	Organism* child = static_cast<Organism*>(new DeadlyNightshade(childPos.x, childPos.y));
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