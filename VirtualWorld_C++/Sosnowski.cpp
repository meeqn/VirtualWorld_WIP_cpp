#include "Sosnowski.h"
#include "World.h"
using namespace boardConsts;
using namespace sosnowskiStats;
Sosnowski::Sosnowski(int posX, int posY) {
	this->setPlant(STRENGTH, posX, posY, SYMBOL);
}
Organism* Sosnowski::createChild(Point childPos) const {
	Organism* child = static_cast<Organism*>(new Sosnowski(childPos.x, childPos.y));
	return child;
}
void Sosnowski::collision(Animal* invader) {
	std::cout << *invader << " ate " << *this << " and died" << std::endl;
	this->getWorld()->moveOrganismToGraveyard(this);
	this->getWorld()->moveOrganismToGraveyard(invader);
}
void Sosnowski::action() {
	int x[DIRECTIONS_NUM] = { 1, -1, 0, 0 };
	int y[DIRECTIONS_NUM] = { 0, 0, 1, -1 };
	Point point(this->getPos().x, this->getPos().y);
	Organism* soonToBeDead;
	for (int i = 0; i < DIRECTIONS_NUM; i++) {
		point.move(x[i], y[i], 1);
		if (this->getWorld()->getBoard()->isPointInBoundaries(point)) {
			soonToBeDead = this->getWorld()->getBoard()->getBoardField(point);
			if (soonToBeDead != nullptr) {
				this->getWorld()->moveOrganismToGraveyard(soonToBeDead);
				this->getWorld()->sp->addKillMessage(this, soonToBeDead);
			}
		}
		point.move(-x[i], -y[i], 1);
	}
}
void Sosnowski::Write(std::ostream& out) const {
	out << "a Sosnowski's Hogweed " << this->giveStats();
}
Sosnowski::~Sosnowski() {
}