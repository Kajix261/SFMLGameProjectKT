#include "Enemy.h"

Enemy::Enemy(sf::Texture &t, sf::Vector2f p, int af) : AnimatedObject(t, p ,af){
	this->setTexture(texture);
	this->setPosition(position);
}

Enemy::~Enemy(){

}

void Enemy::shooting(sf::Time& elapsed_time){
	shoot_time += elapsed_time;
	if (shoot_time.asSeconds() >= 2.0) {
		//setTextureRect(sf::IntRect(450, 0, 30, 37));
		sf::Texture arrow_texture;
		arrow_texture.loadFromFile("resources/arrow.png");
		sf::Vector2f arrow_position;
		arrow_position.x = this->getPosition().x - 20.0;
		arrow_position.y = this->getPosition().y + 30.0;

		auto arrow = new Arrow(arrow_texture, arrow_position);
		arrow->setScale(1.2, 1.2);

		arrows.push_back(arrow);
		shoot_time = sf::Time::Zero;
	}
}



void Enemy::render_arrows(sf::RenderWindow& window){
	for (const auto& arrow : arrows) {
		window.draw(*arrow);
	}
}

void Enemy::clear_arrows(){
	for (auto it = arrows.begin(); it != arrows.end();) {
		if ((*it)->getPosition().x + (*it)->getGlobalBounds().width < 0) {
			delete* it;
			it = arrows.erase(it);
		}
		else {
			it++;
		}
	}
}

void Enemy::update(sf::Time &elapsed_time, float &o_velocity){
	this->animate(elapsed_time);
	for (auto& arrow : arrows) {
		arrow->move((o_velocity - 200) * elapsed_time.asSeconds(), 0.0);
	}
	this->clear_arrows();
	this->shooting(elapsed_time);
}



