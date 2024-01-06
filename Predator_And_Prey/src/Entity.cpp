#include "Entity.h"
#include <cmath>

void Entity::die()
{
	death = std::chrono::high_resolution_clock::now();
	aliveTime = death - birth;
}

void Entity::update()
{
	m_position.x += std::cos(m_angle) * m_velocity;
	m_position.y += std::sin(m_angle) * m_velocity;

	m_distanceTraveled += m_velocity;



	if (m_position.x < 0.f)
	{
		m_position.x = 0.f;
	}
	else if (m_position.x > 970.f)
	{
		m_position.x = 970.f;
	}
	if (m_position.y < 0.f)
	{
		m_position.y = 0.f;
	}
	else if (m_position.y > 570.f)
	{
		m_position.y = 570.f;
	}


	std::chrono::duration<double> timeSinceLastTick = std::chrono::steady_clock::now() - timeOfLastTick;

	if (timeSinceLastTick.count() >= 1)
	{
		health--;
		timeOfLastTick = std::chrono::steady_clock::now();
		secondsPassed++;
	}

	if (secondsPassed == 5)
	{
		secondsPassed = 0;
		if (m_distanceTraveled < 50)
		{
			isDead = true;
		}
		else
		{
			m_distanceTraveled = 0.f;
		}
	}

	if (health == 0)
	{
		isDead = true;
	}

	detectionRange[0] = sf::Vector2f(m_position.x - 150.f, m_position.y - 150.f);
	detectionRange[1] = sf::Vector2f(m_position.x + 150.f, m_position.y + 150.f);

}