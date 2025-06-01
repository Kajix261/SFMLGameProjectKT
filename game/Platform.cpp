#include "Platform.h"

Platform::Platform(sf::Texture& t, sf::Vector2f p) : GraphicalObject(t, p) {
	this->setTexture(texture);
	this->setPosition(position);
}

Platform::~Platform() {

}