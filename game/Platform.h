#pragma once
#include "GraphicalObject.h"

class Platform : public GraphicalObject
{
public:
	Platform(sf::Texture& t, sf::Vector2f p);
	~Platform();

};

