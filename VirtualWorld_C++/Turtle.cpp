#include "Turtle.h"
#include "World.h"
using namespace turtleStats;
Turtle::Turtle(int posX, int posY) {
	this->setAnimal(INITIATIVE, STRENGTH, posX, posY, SYMBOL, MOVE_DIST);
}
Organism* Turtle::createChild(Point childPos) const {
	Organism* animal = static_cast<Organism*>(new Turtle(childPos.x, childPos.y));
	return animal;
}
void Turtle::action() {
	int prob = (rand() % 100) + 1;
	if(prob>75)
		Animal::action();
}
void Turtle::collision(Animal* invader) {

	if (invader->getSymbol() == this->getSymbol()) {
		this->breed(invader);
	}
	else
	{
		World* world = this->getWorld();
		if (invader->getStrength() >= 5) {
			this->organismGetsAttacked(invader);
		}
	}
}
void Turtle::Write(std::ostream& out) const {
	out << "a Turtle " << this->giveStats();
}
Turtle::~Turtle() {
}