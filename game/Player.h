#pragma once
#include "AnimatedObject.h"

enum class State {
	stable,
	in_air,
	passive,

};

class Player : public AnimatedObject
{
private:
	//movement variables
	float jump_velocity = 0;
	float jump_height = 115.0;
	float horizontal_velocity = 600.0;
	float forward_velocity = 200.0;
	float back_velocity = -300.0;
	float state_velocity = 50;
	const float g = 981.0;

	//state
	State state = State::stable;
	State attitude = State::passive;

public:
	//contructors
	Player(sf::Texture t, sf::Vector2f p, int af);
	~Player();
	//movement methods
	void movement(sf::Time& elapsed_time);
	void gravity(sf::Time& elapsed_time);
	//game info
	void lost();
	//info methods
	State get_attitude();
	//update
	void update(sf::Time& elapsed_time);
	void reset();
};




