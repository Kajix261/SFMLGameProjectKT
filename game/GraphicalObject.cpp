#include "GraphicalObject.h"

//constructors
GraphicalObject::GraphicalObject(const sf::Texture& t, sf::Vector2f p) : texture(t), position(p) {
	this->setTexture(texture);
	this->setPosition(position);
}

GraphicalObject::GraphicalObject(sf::Texture t, sf::Vector2f p, sf::IntRect f) : texture(t), position(p), frame(f) {
	this->texture.setRepeated(true);
	this->setTexture(texture);
	this->setTextureRect(frame);
	this->setPosition(position);
}

GraphicalObject::~GraphicalObject() {

}