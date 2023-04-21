#pragma once
#include "Animal.h"
class Fox : public Animal {
protected:
	virtual void Write(std::ostream& out) const override;
	void action() override;
	Organism* createChild(Point childPos) const override;
public:
	Fox(int posX, int posY);
	~Fox() override;
};
