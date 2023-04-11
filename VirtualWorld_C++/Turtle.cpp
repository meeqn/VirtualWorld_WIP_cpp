#include "Turtle.h"
#include "World.h"

Turtle::Turtle(int posX, int posY) {
	this->setAnimal(TURTLE_INITIATIVE, TURTLE_STRENGTH, posX, posY, TURTLE_SYMBOL, TURTLE_MOVE_DIST);
	//std::cout << "Created a Turtle ";
	//this->giveStats();
	//std::cout << "\n";
}
Organism* Turtle::createChild(Point childPos) const {
	Organism* animal = new Turtle(childPos.x, childPos.y);;
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
			this->animalGetsAttacked(invader);
		}
	}
}
void Turtle::Write(std::ostream& out) const {
	std::cout << "a Turtle ";
	this->giveStats();
}
Turtle::~Turtle() {
	std::cout << "Destroyed a Turtle ";
	this->giveStats();
	std::cout << "\n";
}