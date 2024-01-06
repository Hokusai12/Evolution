#pragma once
#include <SFML/Graphics.hpp>

class Food
{
private:
	bool m_isEaten = false;
	sf::Vector2f m_position;

public:
	void setIsEaten(bool eaten) { m_isEaten = eaten; }
	bool getIsEaten() { return m_isEaten; }
	void setPosition(sf::Vector2f position) { m_position = position; }
	sf::Vector2f getPosition() { return m_position; }
	void reset();

	Food();
};

