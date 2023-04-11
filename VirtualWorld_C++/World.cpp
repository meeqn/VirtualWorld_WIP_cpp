#include "World.h"
#include "AnimalStats.h"
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
void World::drawTheBoard() const {
	for (int i = 0; i < this->getSizeY(); i++) {
		for (int j = 0; j < this->getSizeX(); j++) {
			if (this->getBoard()->getBoardField(Point(j,i)) != nullptr)
				this->getBoard()->getBoardField(Point(j, i))->draw();
			else
				printf("%c", BLANK_MAP_SPACE);
		}
		if(i==0)
			printf("\tq - symbols dictionary \t esc - quit");
		printf("\n");
	}
	printf("\n");
}
void World::drawTheSymbolsDictionary() const{
	system("CLS");
	printf("q - return \t esc - quit\n\n");
	printf("ANIMALS:\n");
	printf("\t %c - sheep  %c - wolf  %c - turtle \n \t %c - antelope %c - fox \n", SHEEP_SYMBOL, WOLF_SYMBOL, TURTLE_SYMBOL, ANTELOPE_SYMBOL, FOX_SYMBOL);
	printf("PLANTS:\n");
}

//insertion sort first - initiative, then - strength
void World::sortOrganisms() { //insertion sort; first - initiative, then - strength
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
void World::nextTurn() {
	system("CLS");
	this->sortOrganisms();
	for (int i = 0; i < organismsGroup.size(); i++) {
		if(organismsGroup[i]->isActive())
			organismsGroup[i]->action();

		organismsGroup[i]->activate();
		organismsGroup[i]->Ageing();
	}
	ridOfTheDead();
}

//remove organism from active board and prepare it to be deleted
void World::moveOrganismToGraveyard(Organism* organism) {
	this->getBoard()->setBoardField(organism->getPos(), nullptr);
	organism->death();
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
		if(this->getBoard()->getBoardField(orgVec[i]->getPos())==nullptr)
			this->addOrganismToWorldActive(orgVec[i]);
	}
	std::cout << "Constructed a World size " << this->board->sizeY << "x" << this->board->sizeX << std::endl;
}
World::~World(){
	this->board->~Board();
	for (int i = 0; i < this->organismsGroup.size(); i++)
		this->organismsGroup[i]->~Organism();
	std::cout << "Destroyed a World size " << this->board->sizeY << "x" << this->board->sizeX << std::endl;
}