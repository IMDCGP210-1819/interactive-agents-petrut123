#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Agent.h"
#include "Map.h"
#include "GymTrainer.h"

using namespace std;

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 600;
const int AGENT_COUNT = 3;

std::vector<Agent*> agents;
GymTrainer* trainer;

Map* worldMap;

void DrawCalls(sf::RenderWindow* window)
{
	window->draw(*worldMap->benchSprite);
	window->draw(*worldMap->bikeSprite);
	window->draw(*worldMap->treadMillSprite);
	window->draw(trainer->m_sprite);

	for (size_t i = 0; i < AGENT_COUNT; i++)
		window->draw(agents[i]->m_sprite);
}

int main()
{
	sf::Texture guyTexture;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Interactive Agents!");

	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	worldMap = new Map(WINDOW_WIDTH / MAP_NODE_DIMENSION_X, WINDOW_HEIGHT / MAP_NODE_DIMENSION_Y);

	// Load texture
	guyTexture.loadFromFile("../Assets/guy.png");

	// Create agents
	agents.resize(AGENT_COUNT);
	for (size_t i = 0; i < AGENT_COUNT; i++)
	{
		agents[i] = new Agent(sf::Sprite(guyTexture), worldMap);
		// Set a random position
		agents[i]->m_sprite.setPosition(Random::RandomNumberInRange(WINDOW_WIDTH, 0.f), Random::RandomNumberInRange(WINDOW_HEIGHT, 0.f));
	}
		

	// Create gym trainer
	trainer = new GymTrainer(sf::Sprite(guyTexture), agents);

	// Scale the trainer's sprite up so it's distinguished
	trainer->m_sprite.setScale(1.5f, 1.5f);

	// Bool used to stop holding left click on agents to spam the on click function
	bool onMouseUp = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			/// Click on an entity once to display more information about it in the console and click on it again to disable console output for that entity
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (onMouseUp)
				{
					onMouseUp = false;

					// Get the mouse position
					sf::Vector2i mouse = sf::Mouse::getPosition(window);

					if (trainer->m_sprite.getGlobalBounds().contains(mouse.x, mouse.y))
						trainer->OnClick();

					for (size_t i = 0; i < agents.size(); i++)
					{
						// retrieve the bounding box of the sprite
						sf::FloatRect bounds = agents[i]->m_sprite.getGlobalBounds();

						// Check if mouse is inside the sprite's rect
						if (bounds.contains(mouse.x, mouse.y))
						{
							agents[i]->OnAgentClicked();
						}
					}
				}
			}
			else
				onMouseUp = true;
		}

		for (size_t i = 0; i < agents.size(); i++)
			agents[i]->Update();

		trainer->Update();

		window.clear(sf::Color(255, 111, 97, 100));
		DrawCalls(&window);
		window.display();
	}

	return 0;
}
