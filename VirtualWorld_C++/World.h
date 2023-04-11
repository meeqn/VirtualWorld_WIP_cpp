#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Organism.h"
#include "Animal.h"
#include "Board.h"

class World {

private:
	Board *board;
	std::vector<Organism*> organismsGroup;
	void putOrganismOnBoard(Organism *organism);
	void ridOfTheDead();
	void sortOrganisms();
public:
	World();
	World(int rows, int columns);
	World(int rows, int columns, std::vector<Organism*> organismVec);
	void drawTheBoard() const;
	void drawTheSymbolsDictionary() const;
	int getSizeX() const;
	int getSizeY() const;
	Board* getBoard() const;
	
	void addOrganismToWorldActive(Organism* organism);
	void addOrganismToWorldInactive(Organism* organism);
	void moveAnimalToNextPosition(Animal* organism);
	void moveOrganismToGraveyard(Organism* organism);
	void nextTurn();
	~World();
};
