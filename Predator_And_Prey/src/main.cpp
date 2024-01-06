#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Simulation.h"

#include "Entity.h"
#include "Prey.h"
#include "Predator.h"

#include "NetworkTracker.h"

int main()
{
	Simulation simulation = Simulation();

	simulation.init();

	sf::RenderWindow window(sf::VideoMode(1000, 600), "Predator and Prey");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		simulation.update();

		window.clear();

		simulation.draw(window);

		window.display();
	}

	return 0;
}