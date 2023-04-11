#include "Plant.h"
#include "World.h"
void Plant::setSewingDist(int sewingDist) {
	this->sewingDist = sewingDist;
}
void Plant::setPlant(int strength, int posX, int posY, char sym) {
	this->setStrength(strength);
	this->setPos(posX, posY);
	this->setSymbol(sym);
	this->setInitiative(PLANT_INITIATIVE);
}
void Plant::setPlant(int strength, int posX, int posY, char sym, int sewingDist) {
	Plant::setPlant(strength, posX, posY, sym);
	this->setSewingDist(sewingDist);
}
int Plant::getSewingDist() {
	return this->sewingDist;
}
void Plant::action() {
 	Point offspringPos = this->generateNeighboringPositions(1, this->getSewingDist());
	int prob = (rand() % 100) + 1;
	if (prob > 80) {
		if (!offspringPos.isUndefined()) {
			this->getWorld()->addOrganismToWorldInactive(this->createChild(offspringPos));
		}
	}
}
void Plant::collision(Animal* invader) {
	this->getWorld()->moveOrganismToGraveyard(this);
	this->getWorld()->moveAnimalToNextPosition(invader);
	std::cout << *invader << " has eaten " << *this << "\n";
}
Plant::~Plant() {

}