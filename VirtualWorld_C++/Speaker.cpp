#include "Speaker.h"

Speaker::Speaker() {
	std::cout << "Created a speaker" << std::endl;
}
void Speaker::addMessage(std::string message) {
	this->buffer << message << std::endl;
}
void Speaker::clearMessages() {
	this->buffer.str("");
}
void Speaker::printMessages() {
	std::cout << this->buffer.str();
};
void Speaker::addCreateMessage(Organism* organism) {
	this->buffer << *organism << " was created" << std::endl;
};
void Speaker::addDestroyMessage(Organism* organism) {
	this->buffer << *organism << " was destroyed" << std::endl;
};
void Speaker::addKillMessage(Organism* killer, Organism* victim) {
	this->buffer << *killer << " killed " << *victim << std::endl;
};
void Speaker::addBirthMessage(Animal* parent1, Animal* parent2, Animal* kid) {
	this->buffer << *parent1 << " and " << *parent2 << " had a baby: " << *kid << std::endl;
};
void Speaker::addBirthMessage(Plant* parent, Plant* offspring) {
	this->buffer << *parent << " created sapling " << *offspring << std::endl;
};
void Speaker::addCustomMessage(std::string message) {
	this->buffer << message << std::endl;
}
Speaker::~Speaker() {
	std::cout << "Destroyed a speaker" << std::endl;
}