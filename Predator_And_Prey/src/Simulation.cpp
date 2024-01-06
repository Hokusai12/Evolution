#include "Simulation.h"
#include "Prey.h"
#include "Predator.h"

#include <iostream>

std::vector<Entity*> Simulation::getPreyInRange(sf::Vector2f* detectionRange)
{
	std::vector<Entity*> preyInRange = std::vector<Entity*>();
	for (Prey& prey : m_preyList)
	{
		sf::Vector2f pos = prey.getPosition();
		if (pos.x > detectionRange[0].x && pos.x < detectionRange[1].x && pos.y > detectionRange[0].y && pos.y < detectionRange[1].y && !prey.isDead)
		{
			preyInRange.push_back(&prey);
		}
	}
	return preyInRange;
}

std::vector<Entity*> Simulation::getPredatorInRange(sf::Vector2f* detectionRange)
{
	std::vector<Entity*> predatorInRange = std::vector<Entity*>();
	for (Predator& predator : m_predatorList)
	{
		sf::Vector2f pos = predator.getPosition();
		if (pos.x > detectionRange[0].x && pos.x < detectionRange[1].x && pos.y > detectionRange[0].y && pos.y < detectionRange[1].y && !predator.isDead)
		{
			predatorInRange.push_back(&predator);
		}
	}
	return predatorInRange;
}


std::vector<Food*> Simulation::getFoodInRange(sf::Vector2f* detectionRange)
{
	std::vector<Food*> foodInRange = std::vector<Food*>();

	for (Food& food : m_foodList)
	{
		sf::Vector2f position = food.getPosition();
		if (position.x > detectionRange[0].x && position.x < detectionRange[1].x && position.y > detectionRange[0].y && position.y < detectionRange[1].y)
		{
			foodInRange.push_back(&food);
		}
	}

	return foodInRange;
}

Simulation::Simulation()
{
	textFont.loadFromFile("./resource/HWYGOTH.TTF");
}

void Simulation::init()
{
	for (int i = 0; i < 10; i++)
	{
		Prey prey = Prey();
		m_preyList.push_back(prey);
	}
	for (int i = 0; i < 5; i++)
	{
		Predator predator = Predator();
		m_predatorList.push_back(predator);
	}
	for (int i = 0; i < 10; i++)
	{
		Food food = Food();
		m_foodList.push_back(food);
	}
}

void Simulation::update()
{
	std::vector<int> preyToKill = std::vector<int>();
	std::vector<int> predatorsToKill = std::vector<int>();

	for (int i = 0; i < m_preyList.size(); i++)
	{
		Prey* prey = &m_preyList.at(i);

		(*prey).update();

		sf::Vector2f* entityDetectionRange = (*prey).getDetectionRange();
		std::vector<Entity*> predatorsNearby = getPredatorInRange(entityDetectionRange);
		(*prey).addPredatorsInRange(predatorsNearby);

		std::vector<Food*> nearbyFood = getFoodInRange(entityDetectionRange);
		(*prey).addFoodInRange(nearbyFood);

		if ((*prey).isDead)
		{
			(*prey).die();
			preyToKill.push_back(i);
		}

	}

	for (int i = 0; i < m_predatorList.size(); i++)
	{
		Predator* predator = &m_predatorList.at(i);

		(*predator).update();
		sf::Vector2f* entityDetectionRange = (*predator).getDetectionRange();

		std::vector<Entity*> preyNearby = getPreyInRange(entityDetectionRange);

		(*predator).addPreyInRange(preyNearby);

		if ((*predator).isDead)
		{
			(*predator).die();
			predatorsToKill.push_back(i);
		}
	}
	for (int i = 0; i < predatorsToKill.size(); i++)
	{
		Predator* predator = &m_predatorList.at(predatorsToKill.at(i));

		if ((*predator).getAliveTime() > m_tracker.getPredatorAliveTime())
		{
			m_tracker.setPredatorAliveTime((*predator).getAliveTime());
			m_tracker.setPredatorNetwork((*predator).getNetwork());
			if ((*predator).getPreyEaten() > m_tracker.getPredatorPreyEaten())
			{
				m_tracker.setPredatorPreyEaten((*predator).getPreyEaten());
			}
			std::cout << "Longest Predator Alive Time: " << (*predator).getAliveTime().count() << std::endl;
		}

		m_predatorList.erase(m_predatorList.begin() + (predatorsToKill.at(i) - i));

		Predator newPredator = Predator(m_tracker.getPredatorNetwork());
		m_predatorList.push_back(newPredator);
	}

	for (int i = 0; i < preyToKill.size(); i++)
	{
		Prey* prey = &m_preyList.at(preyToKill.at(i));
		if ((*prey).getAliveTime() > m_tracker.getPreyAliveTime())
		{
			m_tracker.setPreyAliveTime((*prey).getAliveTime());
			m_tracker.setPreyNetwork((*prey).getNetwork());
			std::cout << "Longest Prey Alive Time: " << (*prey).getAliveTime().count() << std::endl;
		}

		m_preyList.erase(m_preyList.begin() + (preyToKill.at(i) - i));

		Prey newPrey = Prey(m_tracker.getPreyNetwork());
		m_preyList.push_back(newPrey);
	}
}

void Simulation::draw(sf::RenderWindow& window)
{
	sf::CircleShape entityCircle(15.f);
	sf::Text entityHealth = sf::Text();

	sf::Vector2f position;

	entityHealth.setFont(textFont);
	entityHealth.setCharacterSize(30);

	for (Prey& prey : m_preyList)
	{
		position = prey.getPosition();

		entityCircle.setFillColor(sf::Color::Green);
		entityHealth.setString(std::to_string(prey.getHealth()));

		entityHealth.setPosition(sf::Vector2f(position.x + 5, position.y - 5));
		entityCircle.setPosition(position);

		window.draw(entityCircle);
		window.draw(entityHealth);
	}

	for (Predator& predator : m_predatorList)
	{
		position = predator.getPosition();
		entityCircle.setFillColor(sf::Color::Red);
		entityHealth.setString(std::to_string(predator.getHealth()));

		entityCircle.setPosition(position);
		entityHealth.setPosition(sf::Vector2f(position.x + 5, position.y - 5));

		window.draw(entityCircle);
		window.draw(entityHealth);
	}
	for (auto food : m_foodList)
	{
		position = food.getPosition();

		entityCircle.setFillColor(sf::Color::Yellow);
		entityCircle.setPosition(position);
		window.draw(entityCircle);
	}
}


