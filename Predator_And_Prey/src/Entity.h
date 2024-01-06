#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include "NeuralNetwork.h"

class Entity
{
protected:
	sf::Vector2f detectionRange[2];
	int m_id;
	int health = 10;
	sf::Vector2f m_position;
	float m_angle;
	float m_velocity;
	float m_distanceTraveled;
	int secondsPassed = 0;
	NeuralNetwork m_nodeNetwork;
	std::chrono::time_point<std::chrono::high_resolution_clock> birth, death, timeOfLastTick;
	std::chrono::duration<double> aliveTime;

public:
	bool canDie = true;
	bool isDead = false;

public:
	int getId() { return m_id; }
	sf::Vector2f getPosition() { return m_position; }
	void setPosition(float xPos, float yPos) { m_position.x = xPos; m_position.y = yPos; }
	void setVelocity(float vel) { m_velocity = vel; }
	float getVelocity() { return m_velocity; }
	void setAngle(float angle) { m_angle = angle; }
	float getAngle() { return m_angle; }
	NeuralNetwork getNetwork() { return m_nodeNetwork; }
	std::chrono::duration<double> getAliveTime() { return aliveTime; }
	sf::Vector2f* getDetectionRange() { return detectionRange; }
	int getHealth() { return health; }

	virtual void update();

	void die();
protected:

};

