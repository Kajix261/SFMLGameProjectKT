#pragma once
#include "AnimatedObject.h";

class Enemy : public AnimatedObject
{

public:

//constructor
	Enemy(sf::Texture &t, sf::Vector2f p, int af);
	~Enemy();

//update
	void update(sf::Time elapsed_time, float& velocity);
};

