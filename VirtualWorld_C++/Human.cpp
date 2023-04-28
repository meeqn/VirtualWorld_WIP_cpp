#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "Human.h"
#include "World.h"
#include "Buttons.h"
#include "boardConsts.h"

using namespace boardConsts;
using namespace buttons;
using namespace humanStats;

Human::Human(int posX, int posY) {
	this->setAnimal(INITIATIVE, STRENGTH, posX, posY, SYMBOL, MOVE_DIST);
	this->state = NULL;
	this->skillTimeout = 0;
	this->skillRemainingTurns = 0;
	this->skillActive = false;
}
int Human::getSkillRemainingTime() {
	return this->skillRemainingTurns;
}
int Human::getSkillTimeout() {
	return this->skillTimeout;
}
void Human::setSkillRemainingTime(int remainingTime){
	this->skillRemainingTurns = remainingTime;
}
void Human::setSkillTimeout(int timeout) {
	this->skillTimeout = timeout;
}
Organism* Human::createChild(Point childPos) const {
	return nullptr;
}
void Human::skillTurnPass() {

	if (this->skillActive == true) {
		if (this->skillRemainingTurns > 0)
			skillRemainingTurns--;

		else if (this->skillRemainingTurns == 0)
			this->skillActive = false;
	}
	else if (this->skillTimeout > 0 && this->skillRemainingTurns==0)
		skillTimeout--;
}
void Human::useSkill() {
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
void Human::setSkillReady(bool isSkillReady) {
	this->skillActive = isSkillReady;
}
void Human::action() {

	this->skillTurnPass();

	this->state = _getch();

	if (this->state == SKILL_BUTTON && this->skillTimeout == 0) {
		this->skillActive = true;
		this->skillRemainingTurns = SKILL_DURATION;
		this->skillTimeout = SKILL_RELOAD_TIME;
		printf("Human used skill!\n");
		this->state = _getch();
	}

	if (this->state == 0 || this->state == 0xE0) {

		this->state = _getch();

		Point next = this->getPos();
		switch (state) {

			case ARR_UP:
				next.move(0, -1, this->getMoveDist());
				break;
			case ARR_DOWN:
				next.move(0, 1, this->getMoveDist());
				break;
			case ARR_LEFT:
				next.move(-1, 0, this->getMoveDist());
				break;
			case ARR_RIGHT:
				next.move(1, 0, this->getMoveDist());
				break;

		}
		state = NULL;
		this->setNextPos(next);

		if (this->getWorld()->getBoard()->isPointInBoundaries(this->getNextPos())) {
			if (this->getWorld()->getBoard()->getBoardField(this->getNextPos()) == nullptr)
				this->getWorld()->moveAnimalToNextPosition(this);
			else {
				if (!this->skillActive)
					this->getWorld()->getBoard()->getBoardField(this->getNextPos())->collision(this);
				else {
					this->useSkill();
					this->getWorld()->moveAnimalToNextPosition(this);
				}
			}
		}
	}
}
void Human::saveOrganism(std::string type, std::ofstream& out) {
	std::stringstream buffer;
	buffer << "human" << "|" << this->getPos().x << "|" << this->getPos().y << "|" << this->getAge() << "|" << this->getStrength() << "|" << this->getSkillRemainingTime() << "|" << this->getSkillTimeout() << std::endl;
	out << buffer.str();
}
void Human::Write(std::ostream& out) const {
	out << "a Human " << this->giveStats();
}
void Human::collision(Animal* invader) {
	if(!this->skillActive)
		Animal::collision(invader);
	else {
		this->useSkill();
	}
}
Human::~Human() {

}