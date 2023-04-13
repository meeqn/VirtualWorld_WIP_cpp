#pragma once
#include "Animal.h"
#include "AnimalStats.h"
#define UNDEFINED -1
class Human : public Animal {
private:
	int state = UNDEFINED;
	int skillCooldown = 0;
	virtual void Write(std::ostream& out) const override;
	Organism* createChild(Point childPos) const override;
public:
	virtual void collision(Animal*invader) override;
	virtual void action() override;
	Human(int posX, int posY);
	~Human();
};