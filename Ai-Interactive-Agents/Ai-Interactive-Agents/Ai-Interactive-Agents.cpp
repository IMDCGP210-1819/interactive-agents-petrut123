#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Agent.h"
#include "Map.h"
using namespace std;

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 600;





Agent* agent;

Map* worldMap;

void DrawCalls(sf::RenderWindow* window)
{
	window->draw(agent->m_sprite);
	window->draw(*worldMap->benchSprite);
	window->draw(*worldMap->bikeSprite);
	window->draw(*worldMap->treadMillSprite);
}

int main()
{
	sf::Texture guyTexture;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Interactive Agents!");

	worldMap = new Map(WINDOW_WIDTH / MAP_NODE_DIMENSION_X, WINDOW_HEIGHT / MAP_NODE_DIMENSION_Y);

	// Load texture
	guyTexture.loadFromFile("../Assets/guy.png");
	// Create agent
	agent = new Agent(sf::Sprite(guyTexture), worldMap);


	std::list<Node*> path;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::A)
				{
					//Test code
					//path = agent->GeneratePath(worldMap->nodes[0], worldMap->nodes[7 * worldMap->width + 5]);
				}
			}
		}

		window.clear(sf::Color(255, 111, 97, 100));
		DrawCalls(&window);
		window.display();

		agent->Update();
	}

	return 0;
}
