#pragma once
#include "Organism.h"
#define DEFAULT_MOVE_DIST 1
class Animal : public Organism{
private:
	Point nextPos;
	int moveDist = DEFAULT_MOVE_DIST;
	void setMoveDist(int dist);

protected:
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
