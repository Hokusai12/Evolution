#include "Food.h"
#include <chrono>
#include <iostream>
Food::Food()
{
	std::srand(std::chrono::steady_clock::now().time_since_epoch().count());
	m_position.x = rand() % 1000;
	m_position.y = rand() % 570;
}

void Food::reset()
{
	m_isEaten = false;
	std::srand(std::chrono::steady_clock::now().time_since_epoch().count());
	m_position.x = rand() % 969;
	m_position.y = rand() % 569;
}