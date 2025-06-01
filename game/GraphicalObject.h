#pragma once
#include <SFML/Graphics.hpp>

class GraphicalObject : public sf::Sprite
{
protected:

	//variables for initializing
	sf::Texture texture;
	sf::Vector2f position;
	sf::IntRect frame;
public:
	//constructors
	GraphicalObject(const sf::Texture& t, sf::Vector2f p);
	GraphicalObject(sf::Texture t, sf::Vector2f p, sf::IntRect f);
	~GraphicalObject();
};

