#pragma once
#include "Plant.h"
#include "PlantStats.h"
class DeadlyNightshade : public Plant {
protected:
	virtual void Write(std::ostream& out) const override;
	Organism* createChild(Point childPos) const override;
	virtual void collision(Animal* secondOrganism) override;
public:
	DeadlyNightshade(int posX, int posY);
	~DeadlyNightshade() override;
};