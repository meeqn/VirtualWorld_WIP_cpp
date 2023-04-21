#pragma once
#include "Organism.h"
#include "AnimalStats.h"
using namespace animalStats;
class Animal : public Organism{
private:
	Point nextPos;
	int moveDist = STANDARD_MOVE_DIST;
protected:
	void setMoveDist(int dist);
	void setNextPos(Point newPos);
	void setNextPos(int newPosX, int newPosY);
	virtual void Write(std::ostream& out) const = 0;
	virtual void setAnimal(int initiative, int strength, int posX, int posY, char sym, int moveDist);
	virtual void action() override;
	virtual void breed(Animal* secondAnimal);
	virtual ~Animal() override;
	void animalGetsAttacked(Animal *invader);
public:
	virtual void collision(Animal* invader) override;
	Point getNextPos() const;
	int getMoveDist() const;
	friend class World;
};
