#pragma once
#include "Animal.h"
class Wolf : public Animal {
protected:
	virtual void Write(std::ostream& out) const override;
	Organism* createChild(Point childPos) const override;
public:
	Wolf(int posX, int posY);
	~Wolf() override;
};