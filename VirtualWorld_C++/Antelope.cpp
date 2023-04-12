#include "Antelope.h"
#include "World.h"
Antelope::Antelope(int posX, int posY) {
	this->setAnimal(ANTELOPE_INITIATIVE, ANTELOPE_STRENGTH, posX, posY, ANTELOPE_SYMBOL, ANTELOPE_MOVE_DIST);
	//std::cout << "Created an Antelope ";
	//this->giveStats();
	//std::cout << "\n";
}
Organism* Antelope::createChild(Point childPos) const {
	Organism* animal = new Antelope(childPos.x, childPos.y);;
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
	std::cout << "an Antelope ";
	this->giveStats();
}
Antelope::~Antelope() {
	std::cout << "Destroyed an Antelope ";
	this->giveStats();
	std::cout << "\n";
}