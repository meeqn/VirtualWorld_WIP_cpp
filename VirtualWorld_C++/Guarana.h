#pragma once
#include "Plant.h"
class Guarana : public Plant {
protected:
	virtual void Write(std::ostream& out) const override;
	Organism* createChild(Point childPos) const override;
	virtual void collision(Animal* secondOrganism) override;
public:
	Guarana(int posX, int posY);
	~Guarana() override;
};