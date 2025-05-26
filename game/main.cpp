#include "Player.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#define HEIGHT 768
#define WIDTH 1366

Player create_player() {

    sf::Texture player_texture;
    player_texture.loadFromFile("resources/character2.png");

    Player player(player_texture, sf::Vector2f(220.0, 150.0), 9);
    player.setScale(2, 2);

    player.add_animation_frame(sf::IntRect(205, 0, 30, 37)); // 1 frame of animation
    player.add_animation_frame(sf::IntRect(255, 0, 30, 37)); // 2 frame
    player.add_animation_frame(sf::IntRect(305, 0, 30, 37)); // 3 frame
    player.add_animation_frame(sf::IntRect(355, 0, 30, 37)); // 4 frame

    return player;
}

//game functions
void over_borderline(Player& player, sf::RenderWindow& window, bool& end) {

    if (player.getPosition().x + player.getGlobalBounds().width <= 0 ||
        player.getPosition().y >= window.getSize().y) {
        end = true;
    }
}

int main()
{
    // Game variables
    srand(static_cast<unsigned int>(time(0)));
    sf::Clock clock;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "PixelRunner");
    window.setFramerateLimit(60);

    // Create hero
    Player player = create_player();

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.movement(elapsed);   // <<< THIS
        player.update(elapsed);     // <<< THIS

        window.clear(sf::Color::Black);
        window.draw(player);
        window.display();
    }
}