#pragma once
#include "Organism.h"
#include "PlantStats.h"
class Plant :public Organism {
private:
	int sewingDist = SOWING_DISTANCE;
	void setSewingDist(int sewingDist);

protected:
	virtual void Write(std::ostream& out) const = 0;
	void setPlant(int strength, int posX, int posY, char sym);
	void setPlant(int strength, int posX, int posY, char sym, int sewingDist);
	virtual void action() override;
	virtual ~Plant() override;

public:
	virtual void collision(Animal* invader) override;
	int getSewingDist();
};
