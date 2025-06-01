#include "Player.h"


Player::Player(sf::Texture t, sf::Vector2f p, int af) : AnimatedObject(t, p, af) {
    this->setTexture(texture);
    this->setPosition(position);

}

Player::~Player() {

}

//movement methods
void Player::gravity(sf::Time& elapsed_time) {
    if (state == State::in_air) {
        jump_velocity += g * elapsed_time.asSeconds();
        position.y += jump_velocity * elapsed_time.asSeconds();
    }
    else if (state == State::stable) {
        jump_velocity = 0;
    }
}

void Player::movement(sf::Time& elapsed_time) {
    //gravitation
    this->gravity(elapsed_time);
    //std::cout <<jump_velocity <<"\n";

    //jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

        if (state == State::stable) {
            jump_velocity = -sqrt(2 * g * jump_height);
            state = State::in_air;
            position.y -= jump_velocity * elapsed_time.asSeconds();
        }
    }

    //left-right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        position.x += back_velocity * elapsed_time.asSeconds();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        position.x += forward_velocity * elapsed_time.asSeconds();
    }

    //down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (state == State::stable) {

            position.y += horizontal_velocity * elapsed_time.asSeconds();
        }


    }

    if (state == State::stable) {
        position.x -= state_velocity * elapsed_time.asSeconds();
    }

    //setting new position
    this->setPosition(position);
}

void Player::collision(std::vector<Set>& sets) {
    bool detected = false;

    for (auto& set : sets) {
        for (auto& e : set.platforms) {
            if (this->getPosition().y + this->getGlobalBounds().height >= e.getPosition().y &&
                this->getPosition().y + this->getGlobalBounds().height <= e.getPosition().y + e.getGlobalBounds().height / 2 &&
                this->getPosition().x + this->getGlobalBounds().width > e.getPosition().x &&
                this->getPosition().x < e.getPosition().x + e.getGlobalBounds().width &&
                jump_velocity >= 0) {

                // std::cout << "Collision detected at platform: " << e.getPosition().x << ", " << e.getPosition().y << "\n";
                detected = true;
                state = State::stable;

                break;
            }
            else {
                state = State::in_air;
            }
        }
        if (detected) {
            break;

        }
    }

}

void Player::lost() {

    object_time = sf::seconds(-2);
    jump_height = 0;
    horizontal_velocity = 0;
    forward_velocity = 0;
    back_velocity = -0;
    state_velocity = 0;
}

void Player::update(sf::Time& elapsed_time, std::vector<Set>& sets) {
    if (attitude == State::passive) {
        this->animate(elapsed_time);
    }
    this->collision(sets);
}

void Player::reset() {
    this->state = State::stable;
    this->attitude = State::passive;
    this->position = sf::Vector2f(220.0, 150.0);
    this->setPosition(position);
    this->setRotation(0);
    this->jump_height = 115.0;
    this->horizontal_velocity = 600.0;
    this->forward_velocity = 200.0;
    this->back_velocity = -300.0;
    this->state_velocity = 50;
}

State Player::get_attitude() {
    return attitude;
}