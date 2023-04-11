#pragma once
#include <iostream>
#include "Point.h"
class World;
class Animal;
class Organism {
#define STARTING_AGE 0
#define DIRECTIONS_NUM 4
enum directions { UP, RIGHT, DOWN, LEFT }; //maybe move directions to world
private:
	char symbol;
	int age = STARTING_AGE,initiative, strength;
	Point pos;
	bool active, dead;
	World* world;

protected:
	virtual void Write(std::ostream& out) const = 0;
	friend std::ostream& operator<<(std::ostream& os, const Organism& organism);
	virtual Organism* createChild(Point childPos) const = 0;
	void draw();

	virtual void action() = 0;

	void setSymbol(char newSymbol);
	void setWorld(World* newWorld);
	void setAge(int newAge);
	void setPos(int newPosX, int newPosY);
	void setPos(Point newPos);
	void setInitiative(int newInitiative);
	void setStrength(int newStrength);
	void activate();
	void deactivate();
	void makeAlive();
	void death();
	void Ageing();
	virtual ~Organism();

public:
	virtual void collision(Animal* invader) = 0;
	World* getWorld() const;
	char getSymbol() const;
	int getAge() const;
	Point getPos() const;
	int getInitiative() const;
	int getStrength() const;
	void giveStats() const;
	bool isActive() const;
	bool isDead() const;
	Point generateNeighboringPositions(const bool needFreePosition, int range) const;
	friend class World;
};
