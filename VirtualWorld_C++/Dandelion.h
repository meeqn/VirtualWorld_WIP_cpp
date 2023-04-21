#pragma once
#include "Plant.h"
class Dandelion : public Plant {
protected:
	virtual void Write(std::ostream& out) const override;
	Organism* createChild(Point childPos) const override;
	virtual void action() override;
public:
	Dandelion(int posX, int posY);
	~Dandelion() override;
};