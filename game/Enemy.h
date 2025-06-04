#pragma once
#include "AnimatedObject.h";
#include "Arrow.h"

class Enemy : public AnimatedObject
{
private:
	//variables for an attack
	sf::Time shoot_time;

public:
	std::vector<Arrow*> arrows;
	//constructor
	Enemy(sf::Texture &t, sf::Vector2f p, int af);
	~Enemy();
	//attack method for an enemy
	void shooting(sf::Time& elapsed_time);
	//rendering
	void render_arrows(sf::RenderWindow& window);
	void clear_arrows();
	//update
	void update(sf::Time& elapsed_time, float& o_velocity);
};

