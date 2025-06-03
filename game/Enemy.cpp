#include "Enemy.h"

Enemy::Enemy(sf::Texture &t, sf::Vector2f p, int af) : AnimatedObject(t, p ,af){
	this->setTexture(texture);
	this->setPosition(position);
}

Enemy::~Enemy(){

}

void Enemy::update(sf::Time elapsed_time, float& velocity){
	this->animate(elapsed_time);
	
}



