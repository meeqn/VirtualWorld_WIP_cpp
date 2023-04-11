#pragma once
#include "Plant.h"
#include "PlantStats.h"
class Grass : public Plant {
protected:
	virtual void Write(std::ostream& out) const override;
	Organism* createChild(Point childPos) const override;
public:
	Grass(int posX, int posY);
	~Grass() override;
};