#include "Arrow.h"

Arrow::Arrow(sf::Texture& t, sf::Vector2f p) : GraphicalObject(t, p)
{
	this->setTexture(texture);
	this->setPosition(position);
}

Arrow::~Arrow()
{
}
