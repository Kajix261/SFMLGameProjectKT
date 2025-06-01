#include "Bonus.h"

Bonus::Bonus(sf::Texture& t, const sf::Vector2f& p) : texture(t){
	this->setTexture(texture);
	this->setPosition(p);
}

Bonus::~Bonus(){

}

//Coin

Coin::Coin(sf::Texture& t, const sf::Vector2f p) : Bonus(t,p){
	this->setTexture(texture);
	this->setPosition(p);

	value = 100;
}

Coin::~Coin(){
	if (this->getPosition().x >= 0.0) {
		std::cout << "Coin collected!\n";
	}
}

bool Coin::interaction(Player& player)
{
	if (player.getGlobalBounds().intersects(this->getGlobalBounds())) {
		player.collected += 1;
		player.score += value;
		return true;
	}
	else {
		return false;
	}
}

//Star

Star::Star(sf::Texture& t, const sf::Vector2f& p) : Bonus(t,p){
	this->setTexture(texture);
	this->setPosition(p);

	value = 1;
}

Star::~Star()
{
	std::cout << "Star picked up!\n";
}

bool Star::interaction(Player& player)
{
	if (player.getGlobalBounds().intersects(this->getGlobalBounds())) {
		player.multiplier += value;

		return true;
	}
	else {
		return false;
	}
}
