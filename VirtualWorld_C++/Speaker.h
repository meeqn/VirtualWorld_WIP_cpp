#pragma once
#include <iostream>
#include <sstream>
#include "Plant.h"
#include "Animal.h"
#include "Organism.h"
class Speaker {
private:
	std::stringstream buffer;
	void addMessage(std::string message);
	void clearMessages();
public:
	Speaker();
	void printMessages();
	void addCreateMessage(Organism* organism);
	void addDestroyMessage(Organism* organism);
	void addKillMessage(Organism* killer, Organism* victim);
	void addBirthMessage(Animal* parent1, Animal* parent2, Animal* kid);
	void addBirthMessage(Plant* parent, Plant* offspring);
	~Speaker();
	friend class World;
};