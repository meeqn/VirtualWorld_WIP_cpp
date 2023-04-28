#include <sstream>   
#include <conio.h>
#include <ctime>
#include <fstream>
#include "World.h"
#include "Speaker.h"
#include "AnimalStats.h"
#include "PlantStats.h"
#include "buttons.h"
#include "AllAnimals.h"
#include "AllPlants.h"

using namespace buttons;

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
	printf("q - symbols dictionary \t esc - quit \t s - save \t d - load \nspace - next turn \t arrow keys - move player \t a - use skill \n");
	printf("r - logs on/off, logs ON = %d\n", this->logsOn);
	if (logsOn)
		this->sp->printMessages();
}

void World::drawTheSymbolsDictionary() const{
	system("CLS");
	printf("q - return \t esc - quit\n\n");

	printf("ANIMALS:\n");
	printf("\t %c - sheep  %c - wolf  %c - turtle \n \t %c - antelope %c - fox \n", sheepStats::SYMBOL, 
		wolfStats::SYMBOL, turtleStats::SYMBOL, antelopeStats::SYMBOL, foxStats::SYMBOL);

	printf("PLANTS:\n");
	printf("\t %c - grass  %c - dandelion %c - guarana \n \t %c - deadly nightshade %c - sosnowski's hogweed \n", grassStats::SYMBOL, dandelionStats::SYMBOL, guaranaStats::SYMBOL,
		deadlyNightshadeStats::SYMBOL, sosnowskiStats::SYMBOL);
}

//insertion sort: first - initiative, then - strength
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

	for (int i = 0; i < organismsGroup.size(); i++) {
		if (organismsGroup[i]->isActive()) {
			if(organismsGroup[i]->getSymbol() == humanStats::SYMBOL){
				system("CLS");
				std::cout << "Your move! ";

				Human* tmpHuman = dynamic_cast<Human*>(organismsGroup[i]);
				if (tmpHuman->getSkillRemainingTime() > 0)
					std::cout << "Remaining skill time: " << tmpHuman->getSkillRemainingTime() << std::endl;
				else if (tmpHuman->getSkillTimeout() > 0)
					std::cout << "Skill ready in " << tmpHuman->getSkillTimeout() << std::endl;
				else
					std::cout << "Skill is ready!" << std::endl;

				this->drawTheState();
			}
			organismsGroup[i]->action();
		}

		organismsGroup[i]->activate();
		organismsGroup[i]->Ageing();
	}
	ridOfTheDead();
	system("CLS");
	printf("Press space to continue! \n");
}

//remove organism from active board and prepare it to be deleted
void World::moveOrganismToGraveyard(Organism* organism) {
	this->getBoard()->setBoardField(organism->getPos(), nullptr);
	organism->death();
}

void World::saving() {
	std::string filename;
	std::cout << "name the save file: ";
	std::cin >> filename;
	filename += ".txt";

	std::stringstream buffer;
	buffer << "world" << "|" << this->getSizeX() << "|" << this->getSizeY()<<std::endl;
	std::ofstream out(filename);
	out << buffer.str();
	for (int i = 0; i < organismsGroup.size(); i++) {
		organismsGroup[i]->saveOrganism("", out);
	}
	out.close();

}

void World::setStatsFromStream(std::string stream, int *posX, int *posY, int *strength, int *age, char* sym) {
	std::string tmpString;
	std::stringstream ld(stream);
	std::getline(ld, tmpString, '|');
	int i = 0;
	while (std::getline(ld, tmpString, '|')) {
		switch (i) {
		case 0:
			*sym = tmpString[0];
			break;
		case 1:
			*posX = stoi(tmpString);
			break;
		case 2:
			*posY = stoi(tmpString);
			break;
		case 3:
			*age = stoi(tmpString);
			break;
		case 4:
			*strength = stoi(tmpString);
			break;
		}
		i++;
	}
}
Human* World::loadHuman(std::string stream) {
	int posX, posY, strength, age, skillTimeout, skillRemainingTime;
	std::string tmpString;
	std::stringstream ld(stream);
	std::getline(ld, tmpString, '|');
	int i = 0;
	while (std::getline(ld, tmpString, '|')) {
		switch (i) {
		case 0:
			posX = stoi(tmpString);
			break;
		case 1:
			posY = stoi(tmpString);
			break;
		case 2:
			age = stoi(tmpString);
			break;
		case 3:
			strength = stoi(tmpString);
			break;
		case 4:
			skillRemainingTime = stoi(tmpString);
			break;
		case 5:
			skillTimeout = stoi(tmpString);
			break;
		}
		i++;
	}
	Human* loaded = new Human(posX, posY);
	loaded->setSkillRemainingTime(skillRemainingTime);
	loaded->setSkillTimeout(skillTimeout);
	loaded->setStrength(strength);
	if (skillRemainingTime == 0 && skillTimeout > 0)
		loaded->setSkillReady(false);
	else if (skillRemainingTime > 0)
		loaded->setSkillReady(true);

	return loaded;
}
Animal* World::loadAnimal(std::string stream) {
	int posX, posY, strength, age;
	char sym;
	this->setStatsFromStream(stream, &posX, &posY, &strength, &age, &sym);
	Animal* loaded = nullptr;
	switch (sym) {
		case antelopeStats::SYMBOL:
			loaded = new Antelope(posX, posY);
			break;
		case wolfStats::SYMBOL:
			loaded = new Wolf(posX, posY);
			break;
		case sheepStats::SYMBOL:
			loaded = new Sheep(posX, posY);
			break;
		case foxStats::SYMBOL:
			loaded = new Fox(posX, posY);
			break;
		case turtleStats::SYMBOL:
			loaded = new Turtle(posX, posY);
			break;
	}
	loaded->setAge(age);
	loaded->setStrength(strength);
	return loaded;
}

Plant* World::loadPlant(std::string stream) {
	int posX, posY, strength, age;
	char sym;
	this->setStatsFromStream(stream, &posX, &posY, &strength, &age, &sym);
	Plant* loaded = nullptr;
	switch (sym) {
		case dandelionStats::SYMBOL:
			loaded = new Dandelion(posX, posY);
			break;
		case deadlyNightshadeStats::SYMBOL:
			loaded = new DeadlyNightshade(posX, posY);
			break;
		case guaranaStats::SYMBOL:
			loaded = new Guarana(posX, posY);
			break;
		case grassStats::SYMBOL:
			loaded = new Grass(posX, posY);
			break;
		case sosnowskiStats::SYMBOL:
			loaded = new Sosnowski(posX, posY);
			break;
	}
	loaded->setAge(age);
	loaded->setStrength(strength);
	return loaded;
}

void World::loading() {
	this->board->~Board();
	this->sp->clearMessages();
	for (int i = 0; i < this->organismsGroup.size(); i++)
		this->organismsGroup[i]->~Organism();
	system("CLS");
	this->organismsGroup.clear();

	std::string filename;
	std::cout << "name the save file: ";
	std::cin >> filename;
	filename += ".txt";

	std::ifstream file(filename);
	std::string str;
	while (std::getline(file, str))
	{
		std::string tmpString;
		std::stringstream ld(str);
		std::getline(ld, tmpString, '|');
		if (tmpString == "world") {
			int sizes[2] = { boardConsts::DEFAULT_BOARD_SIZE_X, boardConsts::DEFAULT_BOARD_SIZE_Y };
			int i = 0;
			while (std::getline(ld, tmpString, '|')) {
				sizes[i] = stoi(tmpString);
				i++;
			}
			this->board = new Board(sizes[0], sizes[1]);
		}
		else if (tmpString == "animal") {
			this->addOrganismToWorldActive(this->loadAnimal(str));
		}
		else if (tmpString == "plant") {
			this->addOrganismToWorldActive(this->loadPlant(str));
		}
		else if (tmpString == "human") {
			this->addOrganismToWorldActive(this->loadHuman(str));
		}
	}
	this->drawTheState();
}
void World::startSimulation() {
	srand(time(NULL));
	this->drawTheState();
	do {
		this->state = _getch();

		switch (this->state) {
		case buttons::SPACE:
			if (this->gameView == GAME_VIEWS::board) {
				this->sp->clearMessages();
				this->nextTurn();
				this->drawTheState();
			}
			break;
		case buttons::q:
			if (this->gameView == GAME_VIEWS::dictionary) {
				system("CLS");
				this->drawTheState();
				this->gameView = GAME_VIEWS::board;
			}
			else {
				this->drawTheSymbolsDictionary();
				this->gameView = GAME_VIEWS::dictionary;
			}
			break;
		case buttons::r:
			if (this->gameView == GAME_VIEWS::board) {
				logsOn = !logsOn;
				system("CLS");
				this->drawTheState();
			}
			break;
		case buttons::ESC:
			this->exit = true;
			break;
		case buttons::s:
			this->saving();
			break;
		case buttons::d:
			this->loading();
			break;
		}
	} while (!this->exit);
}


World::World() {
	this->board = new Board();
	std::cout << "Constructed a World size " << this->board->sizeY << "x" << this->board->sizeX << std::endl;
	std::cout << "Press space to start!" << std::endl;
};
World::World(int rows, int columns) {
	this->board = new Board(columns, rows);
	std::cout << "Constructed a World size " << this->board->sizeY << "x" << this->board->sizeX << std::endl;
	std::cout << "Press space to start!" << std::endl;
};
World::World(int rows, int columns, std::vector<Organism*> orgVec) {
	this->board = new Board(columns, rows);
	for (int i = 0; i < orgVec.size(); i++) {
		if (this->getBoard()->getBoardField(orgVec[i]->getPos()) == nullptr)
			this->addOrganismToWorldActive(orgVec[i]);
		else
			delete orgVec[i];
	}
	this->sortOrganisms();
	std::cout << "Constructed a World size " << this->board->sizeY << "x" << this->board->sizeX << std::endl;
	std::cout << "Press space to start!" << std::endl;
}
World::~World(){
	this->board->~Board();
	this->sp->~Speaker();
	for (int i = 0; i < this->organismsGroup.size(); i++)
		this->organismsGroup[i]->~Organism();
	std::cout << "Destroyed a World size " << this->board->sizeY << "x" << this->board->sizeX << std::endl;
}