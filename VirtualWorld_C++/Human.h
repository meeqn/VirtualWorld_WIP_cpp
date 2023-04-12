#pragma once
#include "Animal.h"
#define UNDEFINED '\n'
class Human : public Animal {
private:
	char state = UNDEFINED;
	virtual void action() override;
public:
	Human(int posX, int posY);
	virtual void collision(Animal* invader);
	~Human()
};