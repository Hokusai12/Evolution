#pragma once
#include "NeuralNetwork.h"
#include "Entity.h"
#include "Food.h"
#include <SFML/Graphics.hpp>

/*
	- Input Node Set
		1 - Distance to nearest Predator
		2 - Distance to nearest Food source
		3 - Distance to nearest Prey
		4 - Rotation
		5 - Position x
		6 - Position y
		7 - Velocity x
		8 - Velocity y
	- Middle Node Set
	- Output Node Set
		1 - Velocity X
		2 - Velocity Y
		3 - Rotation
*/

class Prey : public Entity
{
	//Member Variables
private:
	bool quadrantHasFood[4] = { false, false, false, false };
	bool quadrantHasPredator[4] = { false, false, false, false };
	int m_foodEaten = 0;

	std::vector<Food*> nearbyFood;

	//Member Functions
private:

	std::vector<float> getNetworkInputs();

public:
	Prey(NeuralNetwork* baseNet);
	Prey();

	void addFoodInRange(std::vector<Food*> &foodPositions);

	void setFoodInQuadrants(std::vector<Food*> &foodPositions);
	void addPredatorsInRange(std::vector<Entity*> predatorPositions);

	void update();
};

