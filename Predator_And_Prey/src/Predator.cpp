#define _USE_MATH_DEFINES

#include "Predator.h"


Predator::Predator(NeuralNetwork* baseNet)
{
	std::srand(std::chrono::system_clock::now().time_since_epoch().count());
	m_id = 1;

	timeOfLastTick = std::chrono::steady_clock::now();
	aliveTime = std::chrono::duration<double>();
	birth = std::chrono::high_resolution_clock::now();
	m_position = sf::Vector2f(rand() % 999, rand() % 599);
	m_angle = (rand() % 2000) / 1000.f;
	m_nodeNetwork = NeuralNetwork(8, 2, 2, 8);
	m_nodeNetwork.initializeWithBase(baseNet);
}

Predator::Predator()
{
	std::srand(std::chrono::system_clock::now().time_since_epoch().count());
	m_id = 1;

	timeOfLastTick = std::chrono::steady_clock::now();
	aliveTime = std::chrono::duration<double>();
	birth = std::chrono::high_resolution_clock::now();
	m_position = sf::Vector2f(rand() % 999, rand() % 599);
	m_angle = (rand() % 2000) / 1000.f;
	m_nodeNetwork = NeuralNetwork(8, 2, 2, 8);
	m_nodeNetwork.initializeRandomWeights();
}

void Predator::addPreyInRange(std::vector<Entity*> preyInRange)
{
	quadrantHasPrey[0] = false;
	quadrantHasPrey[1] = false;
	quadrantHasPrey[2] = false;
	quadrantHasPrey[3] = false;

	nearbyPrey = std::vector<Entity*>(preyInRange);

	for (auto prey : nearbyPrey)
	{
		sf::Vector2f pos = prey->getPosition();
		if (pos.x < m_position.x && pos.y < m_position.y)
		{
			quadrantHasPrey[0] = true;
		}
		else if (pos.x > m_position.x && pos.y < m_position.y)
		{
			quadrantHasPrey[1] = true;
		}
		else if (pos.x < m_position.x && pos.y > m_position.y)
		{
			quadrantHasPrey[2] = true;
		}
		else if (pos.x > m_position.x && pos.y > m_position.y)
		{
			quadrantHasPrey[3] = true;
		}
	}
}

std::vector<float> Predator::getNetworkInputs()
{
	std::vector<float> inputs;
	for (auto hasPrey : quadrantHasPrey)
	{
		inputs.push_back(hasPrey);
	}
	inputs.push_back(m_velocity);
	inputs.push_back(m_angle / (2.f * M_PI));
	inputs.push_back(std::abs(m_position.x - 500) / 500.f);
	inputs.push_back(std::abs(m_position.y - 300) / 300.f);

	return inputs;
}

void Predator::update()
{
	for (auto prey : nearbyPrey)
	{
		if (prey->getId() == 0)
		{
			sf::Vector2f preyPos = prey->getPosition();
			if (preyPos.x > m_position.x - 30.f && preyPos.x < m_position.x + 30.f 
				&& preyPos.y > m_position.y - 30.f && preyPos.y < m_position.y + 30.f
				&& prey->isDead == false)
			{
				prey->isDead = true;
				preyEaten++;
				health = 10;
			}
		}
	}

	std::vector<float> inputs = getNetworkInputs();
	std::vector<float> outputValues = m_nodeNetwork.getOutputs(inputs);

	m_velocity = outputValues[0] / 2.f;
	m_angle = outputValues[1] * 2.f * M_PI;

	Entity::update();
}