#include "Plant.h"
#include "World.h"
void Plant::setSowingDist(int sewingDist) {
	this->sowingDist = sewingDist;
}
void Plant::setPlant(int strength, int posX, int posY, char sym) {
	this->setStrength(strength);
	this->setPos(posX, posY);
	this->setSymbol(sym);
	this->setInitiative(PLANT_INITIATIVE);
}
void Plant::setPlant(int strength, int posX, int posY, char sym, int sewingDist) {
	Plant::setPlant(strength, posX, posY, sym);
	this->setSowingDist(sewingDist);
}
int Plant::getSowingDist() {
	return this->sowingDist;
}
void Plant::action() {
 	Point offspringPos = this->getWorld()->getBoard()->generateRandomNeighboringPosition(1, this->getSowingDist(), this);
	int prob = (rand() % 100) + 1;
	if (prob > 80) {
		if (!offspringPos.isUndefined()) {
			Organism* sapling = this->createChild(offspringPos);
			this->getWorld()->addOrganismToWorldInactive(sapling);
			//this->getWorld()->sp->addBirthMessage(this, (Plant*)sapling);
		}
	}
}
void Plant::collision(Animal* invader) {
	World* world = this->getWorld();
	if (this->getStrength() < invader->getStrength()) { //attacked and loses fight
		world->moveOrganismToGraveyard(this);
		world->moveAnimalToNextPosition(invader);
		this->getWorld()->sp->addKillMessage(invader, this);
	}
	else { //defends itself
		world->moveOrganismToGraveyard(invader);
		this->getWorld()->sp->addKillMessage(this, invader);
	}
}
Plant::~Plant() {

}