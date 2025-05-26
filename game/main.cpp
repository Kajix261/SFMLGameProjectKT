#include <iostream>

class Enemy
{
public:
	int health = 0;
	int damage = 0;

	void Kill()
	{
		std::cout << "Kill" << std::endl;
	}

	void Heal()
	{
		health += 10;
		std::cout << "My health = "<<health << std::endl;
	}

	void Walk()
	{
		std::cout << "Walk" << std::endl;
	}
};

int main()
{
	Enemy goblin;

	goblin.health = 100;
	goblin.damage = 50;
	//goblin.Walk();

	std::cout << "Goblin stats: " << std::endl;
	std::cout << goblin.health << std::endl;
	std::cout << goblin.damage << std::endl;


	Enemy Dragon;
	Dragon.health = 200;
	Dragon.damage = 100;

	std::cout << "Dragon stats: " << std::endl;
	std::cout << Dragon.health << std::endl;
	std::cout << Dragon.damage << std::endl;

	return 0;
}





