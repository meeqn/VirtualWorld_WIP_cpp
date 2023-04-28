#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include "Organism.h"
#include "Animal.h"
#include "Board.h"
#include "Human.h"
#include "Speaker.h"
#include "boardConsts.h"
#define STARTING_STATE -1

enum GAME_VIEWS { board, dictionary };

class World {
	GAME_VIEWS gameView = GAME_VIEWS::board;
	bool exit = false, logsOn = true;
	int state = STARTING_STATE;
private:
	Board *board;
	std::vector<Organism*> organismsGroup;
	void putOrganismOnBoard(Organism *organism);
	void ridOfTheDead();
	void sortOrganisms();
	void nextTurn();
	void saving();
	void loading();
	Animal* loadAnimal(std::string stream);
	Plant* loadPlant(std::string stream);
	Human* loadHuman(std::string stream);
	void setStatsFromStream(std::string stream, int* posX, int* posY, int* strength, int*age, char* sym);
public:
	Speaker* sp = new Speaker();
	World();
	World(int rows, int columns);
	World(int rows, int columns, std::vector<Organism*> organismVec);

	void drawTheState() const;
	void drawTheSymbolsDictionary() const;
	int getSizeX() const;
	int getSizeY() const;
	Board* getBoard() const;
	
	void startSimulation();
	void addOrganismToWorldActive(Organism* organism);
	void addOrganismToWorldInactive(Organism* organism);
	void moveAnimalToNextPosition(Animal* organism);
	void moveOrganismToGraveyard(Organism* organism);
	~World();
};
