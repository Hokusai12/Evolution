#define _USE_MATH_DEFINES

#include "Prey.h"


Prey::Prey(NeuralNetwork* baseNet)
{
	std::srand(std::chrono::system_clock::now().time_since_epoch().count());
	m_id = 0;

	timeOfLastTick = std::chrono::steady_clock::now();
	aliveTime = std::chrono::duration<double>();
	birth = std::chrono::high_resolution_clock::now();
	m_position = sf::Vector2f(rand() % 999, rand() % 599);
	m_angle = (rand() % 2000) / 1000.f;
	m_nodeNetwork = NeuralNetwork(12, 2, 2, 12);
	m_nodeNetwork.initializeWithBase(baseNet);
}

Prey::Prey()
{
	std::srand(std::chrono::system_clock::now().time_since_epoch().count());
	m_id = 0;
	aliveTime = std::chrono::duration<double>();

	timeOfLastTick = std::chrono::steady_clock::now();
	birth = std::chrono::high_resolution_clock::now();
	m_position = sf::Vector2f(rand() % 999, rand() % 599);
	m_angle = (rand() % 2000) / 1000.f;
	m_nodeNetwork = NeuralNetwork(12, 2, 2, 12);
	m_nodeNetwork.initializeRandomWeights();
}

void Prey::addFoodInRange(std::vector<Food*> &foodPositions)
{
	nearbyFood = std::vector<Food*>(foodPositions);
}

void Prey::setFoodInQuadrants(std::vector<Food*> &foodPositions)
{
	quadrantHasFood[0] = false;
	quadrantHasFood[1] = false;
	quadrantHasFood[2] = false;
	quadrantHasFood[3] = false;

	for (auto food : foodPositions)
	{
		sf::Vector2f pos = food->getPosition();
		if (pos.x < m_position.x && pos.y < m_position.y)
		{
			quadrantHasFood[0] = true;
		}
		else if (pos.x > m_position.x && pos.y < m_position.y)
		{
			quadrantHasFood[1] = true;
		}
		else if (pos.x < m_position.x && pos.y > m_position.y)
		{
			quadrantHasFood[2] = true;
		}
		else if (pos.x > m_position.x && pos.y > m_position.y)
		{
			quadrantHasFood[3] = true;
		}
	}
}

void Prey::addPredatorsInRange(std::vector<Entity*> predatorPositions)
{
	quadrantHasPredator[0] = false;
	quadrantHasPredator[1] = false;
	quadrantHasPredator[2] = false;
	quadrantHasPredator[3] = false;

	for (auto predator : predatorPositions)
	{
		sf::Vector2f pos = predator->getPosition();
		if (pos.x < m_position.x && pos.y < m_position.y)
		{
			quadrantHasPredator[0] = true;
		}
		else if (pos.x > m_position.x && pos.y < m_position.y)
		{
			quadrantHasPredator[1] = true;
		}
		else if (pos.x < m_position.x && pos.y > m_position.y)
		{
			quadrantHasPredator[2] = true;
		}
		else if (pos.x > m_position.x && pos.y > m_position.y)
		{
			quadrantHasPredator[3] = true;
		}
	}
}



std::vector<float> Prey::getNetworkInputs()
{
	std::vector<float> inputs;
	for (auto hasFood : quadrantHasFood)
	{
		inputs.push_back(hasFood);
	}
	for (auto hasPredator : quadrantHasPredator)
	{
		inputs.push_back(hasPredator);
	}
	inputs.push_back(m_velocity);
	inputs.push_back(m_angle / (2.f * M_PI));
	inputs.push_back(std::abs(m_position.x - 500) / 500.f);
	inputs.push_back(std::abs(m_position.y - 300) / 300.f);
	

	return inputs;
}


void Prey::update()
{
	for (auto food : nearbyFood)
	{
		sf::Vector2f position = food->getPosition();
		if (position.x > m_position.x - 30.f && position.x < m_position.x + 30.f
			&& position.y > m_position.y - 30.f && position.y < m_position.y + 30.f)
		{
			food->setIsEaten(true);
			food->reset();
			m_foodEaten++;
			health = 10;
		}
	}

	std::vector<float> inputs = getNetworkInputs();
	std::vector<float> outputValues = m_nodeNetwork.getOutputs(inputs);

	m_velocity = outputValues[0] / 2.f;
	m_angle = outputValues[1] * 2.f * M_PI;

	Entity::update();
}
