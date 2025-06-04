#pragma once
#include "GraphicalObject.h";

class Arrow : public GraphicalObject
{
private:
	float speed = 150.0;

public:
	Arrow(sf::Texture& t, sf::Vector2f p);
	~Arrow();
};

