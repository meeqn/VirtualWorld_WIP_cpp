#include <iostream>
#include <cstdlib>
#include <ctime>
#include "World.h"
#include "AllAnimals.h"
#include "AllPlants.h"
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
	World braveNewWorld(20, 20, populateStart());
	braveNewWorld.addPlayer(new Human(5, 5));
	//todo saving/loading
	//todo maybe namespaces for defines
	braveNewWorld.startSimulation();
	return 0;
}