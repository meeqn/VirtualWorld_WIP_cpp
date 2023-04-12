#pragma once
#include "Plant.h"
#include "PlantStats.h"
class Sosnowski : public Plant {
protected:
	virtual void Write(std::ostream& out) const override;
	Organism* createChild(Point childPos) const override;
	virtual void collision(Animal* secondOrganism) override;
	virtual void action() override;
public:
	Sosnowski(int posX, int posY);
	~Sosnowski() override;
};