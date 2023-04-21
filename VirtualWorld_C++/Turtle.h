#pragma once
#include "Animal.h"
class Turtle : public Animal {
protected:
	virtual void Write(std::ostream& out) const override;
	void action() override;
	virtual void collision(Animal* secondOrganism) override;
	Organism* createChild(Point childPos) const override;
public:
	Turtle(int posX, int posY);
	~Turtle() override;
};
