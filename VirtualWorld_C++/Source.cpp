#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "World.h"
#include "AllAnimals.h"
#include "AllPlants.h"
#define SPACE 32
#define ESC 27
#define q 113
#define STARTING_STATE '\n'
using namespace std;

vector <Organism*> populateStart() {
	vector <Organism*> orgVec;
	orgVec.push_back(new Sheep(0, 0));
	orgVec.push_back(new Sheep(1, 2));
	orgVec.push_back(new Wolf(6, 9));
	orgVec.push_back(new Wolf(8, 9));
	orgVec.push_back(new Turtle(7, 9));
	orgVec.push_back(new Antelope(4, 4));
	orgVec.push_back(new Fox(8, 4));
	orgVec.push_back(new Grass(5, 4));
	orgVec.push_back(new Grass(6, 4));
	orgVec.push_back(new DeadlyNightshade(7, 5));
	orgVec.push_back(new DeadlyNightshade(7, 6));
	orgVec.push_back(new DeadlyNightshade(7, 7));
	orgVec.push_back(new Sosnowski(3, 7));
	orgVec.push_back(new Sosnowski(0, 7));
	orgVec.push_back(new Dandelion(2, 2));
	orgVec.push_back(new Guarana(9, 9));
	return orgVec;
}

int main() {
	srand(time(NULL));
	bool gameView = 1, exit = false;
	char state = STARTING_STATE;

	World* braveNewWorld = new World(20, 20, populateStart());
	braveNewWorld->drawTheBoard();
	do {
		state = _getch();\

		switch ((int)state) {
		case SPACE:
			if (gameView == 1) {
				braveNewWorld->nextTurn();
				braveNewWorld->drawTheBoard();
			}
			break;
		case q:
			if (!gameView) {
				system("CLS");
				braveNewWorld->drawTheBoard();
			}
			else {
				braveNewWorld->drawTheSymbolsDictionary();
			}
			gameView = !gameView;
			break;
		case ESC:
			exit = true;
			break;
		}
	} while (!exit);
	delete braveNewWorld;
	return 0;
}