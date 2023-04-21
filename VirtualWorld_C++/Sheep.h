#pragma once
#include "Animal.h"
class Sheep : public Animal {
protected:
	virtual void Write(std::ostream& out) const override;
	Organism* createChild(Point childPos) const override;
public:
	Sheep(int posX, int posY);
	~Sheep() override;
};
