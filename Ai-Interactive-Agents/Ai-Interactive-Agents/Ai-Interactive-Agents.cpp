#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 600), "Interactive Agents!");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}

void SpawnAgents() 
{

}