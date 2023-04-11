#include "Organism.h"
#include "World.h"
std::ostream& operator<<(std::ostream& os, const Organism& organism) {
	organism.Write(os);
	return os;
}

void Organism::giveStats() const {
	std::cout << "I:" << this->getInitiative() << " S:" << this->getStrength() << " position: [" << this->getPos().x << "," << this->getPos().y << "]";
}
World* Organism::getWorld() const {
	return this->world;
}
char Organism::getSymbol() const {
	return this->symbol;
}
int Organism::getAge() const {
	return this->age;
}
Point Organism::getPos() const {
	return this->pos;
}
int Organism::getInitiative() const {
	return this->initiative;
}
int Organism::getStrength() const {
	return this->strength;
}
//modified
void Organism::setWorld(World* newWorld) {
	this->world=newWorld;
};
void Organism::setSymbol(char newSymbol) {
	this->symbol = newSymbol;
}
void Organism::setAge(int newAge) {
	this->age = newAge;
}
void Organism::setPos(int newPosX, int newPosY) {
	this->pos = Point(newPosX, newPosY);
}
void Organism::setPos(Point newPos) {
	this->pos = newPos;
}
void Organism::setInitiative(int newInitiative) {
	this->initiative = newInitiative;
}
void Organism::setStrength(int newStrength) {
	this->strength = newStrength;
}
void Organism::draw() {
	printf("%c", this->getSymbol());
}

//modified
void Organism::activate() {
	this->active = true;
}
void Organism::deactivate() {
	this->active = false;
}
bool Organism::isActive() const{
	return active;
}
void Organism::makeAlive() {
	this->dead = false;
}
void Organism::death() {
	this->deactivate();
	this->dead = true;
}
bool Organism::isDead() const {
	return this->dead;
}

Point Organism::generateNeighboringPositions(const bool needFreePosition, int range) const {
	int move;
	unsigned short control = 0b0000;
	Point newPos;
	do {
		move = rand() % DIRECTIONS_NUM;
		newPos.x = this->getPos().x;
		newPos.y = this->getPos().y;
		switch (move) {
		case directions::UP:
			newPos.move(0, -1, range);
			control = control | 0b1000;
			break;
		case directions::RIGHT:
			newPos.move(1, 0, range);
			control = control | 0b0100;
			break;
		case directions::DOWN:
			newPos.move(0, 1, range);
			control = control | 0b0010;
			break;
		case directions::LEFT:
			newPos.move(-1, 0, range);
			control = control | 0b0001;
			break;
		}
		if (control == 0b1111) {
			newPos.x = UNDEFINED;
			newPos.y = UNDEFINED;
			return newPos;
		}
	} while (!this->getWorld()->getBoard()->isPointInBoundaries(newPos) ||
		(needFreePosition == true && this->getWorld()->getBoard()->getBoardField(newPos) != nullptr));
	return newPos;
}
void Organism::Ageing() {
	this->age++;
}
Organism::~Organism() {
}