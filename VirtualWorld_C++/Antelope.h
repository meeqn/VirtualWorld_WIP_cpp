#pragma once
#include "Animal.h"
class Antelope : public Animal {
protected:
	virtual void Write(std::ostream& out) const override;
	virtual void collision(Animal* secondOrganism) override;
	Organism* createChild(Point childPos) const override;
public:
	Antelope(int posX, int posY);
	~Antelope() override;
};
