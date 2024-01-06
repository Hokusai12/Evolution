#pragma once
#include "NetworkTracker.h"
#include "Predator.h"
#include "Prey.h"
#include <vector>
#include <chrono>
#include "Entity.h"
#include "Food.h"

class Simulation
{
	//Member Variables
private:
	NetworkTracker m_tracker;
	std::vector<Predator> m_predatorList;
	std::vector<Prey> m_preyList;
	std::vector<Food> m_foodList;

	sf::Font textFont;

	std::chrono::time_point<std::chrono::steady_clock> m_generationStartTime;


	//Member Functions
private:
	std::vector<Entity*> getPreyInRange(sf::Vector2f* detectionRange);
	std::vector<Entity*> getPredatorInRange(sf::Vector2f* detectionRange);
	std::vector<Food*> getFoodInRange(sf::Vector2f* detectionRange);


public:
	Simulation();
	void init();
	void update();
	void draw(sf::RenderWindow& window);
};

