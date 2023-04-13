#include <sstream>   
#include <conio.h>
#include <ctime>
#include "World.h"
#include "Speaker.h"
#include "AnimalStats.h"
#include "PlantStats.h"
#define SPACE 32
#define ESC 27
#define q 113
#define r 114
int World::getSizeX() const {
	return this->board->sizeX;
}
int World::getSizeY() const {
	return this->board->sizeY;
}
Board* World::getBoard() const{
	return this->board;
}
void World::putOrganismOnBoard(Organism *organism) {
	this->getBoard()->setBoardField(organism->getPos(), organism);
}

void World::addPlayer(Human* player) {
	this->player = player;
	player->activate();
	player->setWorld(this);
	putOrganismOnBoard(player);
}

//used for adding before simulation
void World::addOrganismToWorldActive(Organism* organism){
	this->organismsGroup.push_back(organism);
	organism->activate();
	organism->setWorld(this);
	putOrganismOnBoard(organism);
}

//used for adding newborns so they dont move in first turn
void World::addOrganismToWorldInactive(Organism* organism) {
	this->addOrganismToWorldActive(organism);
	organism->deactivate();
}

//free memory of organisms from graveyard
void World::ridOfTheDead() {
	for (int i = 0; i < this->organismsGroup.size(); i++) {
		if (this->organismsGroup[i]->isDead()) {
			delete this->organismsGroup[i];
			this->organismsGroup.erase(this->organismsGroup.begin() + i);
			i--;
		}
	}
}

void World::moveAnimalToNextPosition(Animal* animal) {
	this->getBoard()->setBoardField(animal->getPos(), nullptr);
	this->getBoard()->setBoardField(animal->getNextPos(), animal);
	animal->setPos(animal->getNextPos());
}

void World::drawTheState() const {
	this->getBoard()->drawTheBoard();
	printf("q - symbols dictionary \t esc - quit \nspace - next turn \t arrow keys - move player \n");
	printf("r - logs on/off, logs ON = %d\n", this->logsOn);
}

void World::drawTheSymbolsDictionary() const{
	system("CLS");
	printf("q - return \t esc - quit\n\n");
	printf("ANIMALS:\n");
	printf("\t %c - sheep  %c - wolf  %c - turtle \n \t %c - antelope %c - fox \n", SHEEP_SYMBOL, WOLF_SYMBOL, TURTLE_SYMBOL, ANTELOPE_SYMBOL, FOX_SYMBOL);
	printf("PLANTS:\n");
	printf("\t %c - grass  %c - dandelion %c - guarana \n \t %c - deadly nightshade %c - sosnowski's hogweed \n", GRASS_SYMBOL, DANDELION_SYMBOL, GUARANA_SYMBOL, DEADLY_NIGHTSHADE_SYMBOL, SOSNOWSKI_SYMBOL);
}

//insertion sort first - initiative, then - strength
void World::sortOrganisms() {
	int i, j, n = organismsGroup.size();
	Organism* keyOrganism;
	for (i = 1; i < n; i++)
	{
		keyOrganism = organismsGroup[i];
		j = i - 1;

		while (j >= 0 && (organismsGroup[j]->getInitiative() < keyOrganism->getInitiative()
			|| (organismsGroup[j]->getInitiative() == keyOrganism->getInitiative()
				&& organismsGroup[j]->getAge() < keyOrganism->getAge())))
		{
			organismsGroup[j + 1] = organismsGroup[j];
			j = j - 1;
		}
		organismsGroup[j + 1] = keyOrganism;
	}
}
void World::nextTurn() { //todo human action separately
	this->sortOrganisms();
	if (this->player != nullptr) {
		if (this->player->isDead()) {
			this->player->~Human();
			this->player = nullptr;
		}
		else {
			this->player->action();
			system("CLS");
			this->drawTheState();
		}
	}
	for (int i = 0; i < organismsGroup.size(); i++) {
		if(organismsGroup[i]->isActive())
			organismsGroup[i]->action();

		organismsGroup[i]->activate();
		organismsGroup[i]->Ageing();
	}
	ridOfTheDead();
	system("CLS");
}

//remove organism from active board and prepare it to be deleted
void World::moveOrganismToGraveyard(Organism* organism) {
	this->getBoard()->setBoardField(organism->getPos(), nullptr);
	organism->death();
}

void World::startSimulation() {
	srand(time(NULL));
	this->drawTheState();
	do {
		this->state = _getch();

		switch (this->state) {
		case SPACE:
			if (this->gameView == GAME_VIEWS::board) {
				this->sp->clearMessages();
				this->nextTurn();

				this->drawTheState();
				if(logsOn)
					this->sp->printMessages();
			}
			break;
		case q:
			if (this->gameView == GAME_VIEWS::dictionary) {
				system("CLS");
				this->drawTheState();
				if(logsOn)
					this->sp->printMessages();
				this->gameView = GAME_VIEWS::board;
			}
			else {
				this->drawTheSymbolsDictionary();
				this->gameView = GAME_VIEWS::dictionary;
			}
			break;
		case r:
			if (this->gameView == GAME_VIEWS::board) {
				logsOn = !logsOn;
				system("CLS");
				this->drawTheState();
				if (logsOn)
					this->sp->printMessages();
			}
			break;
		case ESC:
			this->exit = true;
			break;
		}
	} while (!this->exit);
}
World::World() {
	this->board = new Board();
	std::cout << "Constructed a World size " << this->board->sizeY << "x" << this->board->sizeX << std::endl;
};
World::World(int rows, int columns) {
	this->board = new Board(columns, rows);
	std::cout << "Constructed a World size " << this->board->sizeY << "x" << this->board->sizeX << std::endl;
};
World::World(int rows, int columns, std::vector<Organism*> orgVec) {
	this->board = new Board(columns, rows);
	for (int i = 0; i < orgVec.size(); i++) {
		if (this->getBoard()->getBoardField(orgVec[i]->getPos()) == nullptr)
			this->addOrganismToWorldActive(orgVec[i]);
		else
			delete orgVec[i];
	}
	std::cout << "Constructed a World size " << this->board->sizeY << "x" << this->board->sizeX << std::endl;
}
World::~World(){
	this->board->~Board();
	this->sp->~Speaker();
	if(this->player!=nullptr)
		this->player->~Human();
	for (int i = 0; i < this->organismsGroup.size(); i++)
		this->organismsGroup[i]->~Organism();
	std::cout << "Destroyed a World size " << this->board->sizeY << "x" << this->board->sizeX << std::endl;
}