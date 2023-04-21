#include "Antelope.h"
#include "World.h"
using namespace antelopeStats;

Antelope::Antelope(int posX, int posY) {
	this->setAnimal(INITIATIVE, STRENGTH, posX, posY, SYMBOL, MOVE_DIST);
}
Organism* Antelope::createChild(Point childPos) const {
	Organism* animal = static_cast<Organism*>(new Antelope(childPos.x, childPos.y));
	return animal;
}
void Antelope::collision(Animal* invader) {
	if (invader->getSymbol() == this->getSymbol()) {
		this->breed(invader);
	}
	else
	{
		World* world = this->getWorld();
		int prob = (rand() % 100) + 1;
		if (prob >= 50) {
			Point escapePos = this->getWorld()->getBoard()->generateRandomNeighboringPosition(true, 1, this);
			if (!escapePos.isUndefined()) {
				this->setNextPos(escapePos);
				world->moveAnimalToNextPosition(this);
				world->moveAnimalToNextPosition(invader);
			}
		}
		else {
			this->animalGetsAttacked(invader);
		}
	}
}
void Antelope::Write(std::ostream& out) const {
	out << "an Antelope " << this->giveStats();
}
Antelope::~Antelope() {
}