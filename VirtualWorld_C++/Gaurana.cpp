#include "Guarana.h"
#include "World.h"

Guarana::Guarana(int posX, int posY) {
	this->setPlant(GUARANA_STRENGTH, posX, posY, GUARANA_SYMBOL);
}
Organism* Guarana::createChild(Point childPos) const {
	Organism* child = new Guarana(childPos.x, childPos.y);;
	return child;
}
void Guarana::collision(Animal* invader) {
	std::cout << *invader << " ate " << *this << " and got increase in strength!" << std::endl;
	invader->setStrength(invader->getStrength() + 3);
}
void Guarana::Write(std::ostream& out) const {
	out << "a Guarana " << this->giveStats();
}
Guarana::~Guarana() {
}