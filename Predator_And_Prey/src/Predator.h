#pragma once
#include "NeuralNetwork.h"
#include "Entity.h"
#include <chrono>

class Predator : public Entity
{	//Member Variables
private:
	int preyEaten = 0;
	bool quadrantHasPrey[4] = {false, false, false, false};
	std::vector<Entity*> nearbyPrey;

	//Member Functions
private:

	std::vector<float> getNetworkInputs();
public:
	Predator(NeuralNetwork* baseNet);
	Predator();

	void addPreyInRange(std::vector<Entity*> preyInRange);

	int getPreyEaten() { return preyEaten; }

	void update();
};


