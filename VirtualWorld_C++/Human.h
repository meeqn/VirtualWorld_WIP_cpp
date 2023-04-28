#pragma once
#include "Animal.h"
#define UNDEFINED -1
class Human : public Animal {
private:
	int state, skillTimeout, skillRemainingTurns;
	bool skillActive;
	virtual void Write(std::ostream& out) const override;
	Organism* createChild(Point childPos) const override;
	void useSkill();
	void skillTurnPass();
public:
	void setSkillTimeout(int timeout);
	void setSkillRemainingTime(int remainingTime);
	void setSkillReady(bool isSkillReady);
	int getSkillTimeout();
	int getSkillRemainingTime();
	virtual void saveOrganism(std::string type, std::ofstream& out) override;
	virtual void collision(Animal*invader) override;
	virtual void action() override;
	Human(int posX, int posY);
	~Human();
};