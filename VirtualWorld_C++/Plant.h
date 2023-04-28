#pragma once
#include "Organism.h"
#include "PlantStats.h"
using namespace plantStats;
class Plant :public Organism {
private:
	int sowingDist = SOWING_DISTANCE;
	void setSowingDist(int sewingDist);

protected:
	virtual void Write(std::ostream& out) const = 0;
	void setPlant(int strength, int posX, int posY, char sym);
	void setPlant(int strength, int posX, int posY, char sym, int sewingDist);
	virtual void action() override;
	virtual ~Plant() override;

public:
	virtual void saveOrganism(std::string type, std::ofstream& out) override;
	virtual void collision(Animal* invader) override;
	int getSowingDist();
};
