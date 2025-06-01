#include "Player.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#define HEIGHT 768
#define WIDTH 1366
#define HALF 0.5, 0.5
#define LIMIT 1200


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


Set create_starting_set() {
    Set set;
    sf::Texture ground_platform_texture;
    ground_platform_texture.loadFromFile("resources/ground_platform.png");

    set.add_platform(ground_platform_texture, sf::Vector2f(50.0, 600.0), sf::Vector2f(HALF));

    return set;
}

Set create_set_1() {
    Set set;
    sf::Texture platform_texture;

    platform_texture.loadFromFile("resources/platform.png");

    set.add_platform(platform_texture, sf::Vector2f(WIDTH, 600.0), sf::Vector2f(HALF));
    set.add_platform(platform_texture, sf::Vector2f(WIDTH + 200.0, 510.0), sf::Vector2f(HALF));
    set.add_platform(platform_texture, sf::Vector2f(WIDTH + 400.0, 420.0), sf::Vector2f(HALF));
    set.add_platform(platform_texture, sf::Vector2f(WIDTH + 600.0, 330.0), sf::Vector2f(HALF));

    return set;
}

Set create_set_2() {
    Set set;
    sf::Texture platform_texture;
    sf::Texture small_platform_texture;

    platform_texture.loadFromFile("resources/platform.png");
    small_platform_texture.loadFromFile("resources/small_platform.png");

    set.add_platform(platform_texture, sf::Vector2f(WIDTH, 600), sf::Vector2f(HALF));
    set.add_platform(small_platform_texture, sf::Vector2f(WIDTH + 250, 550), sf::Vector2f(HALF));
    set.add_platform(platform_texture, sf::Vector2f(WIDTH + 500, 600), sf::Vector2f(HALF));
    set.add_platform(small_platform_texture, sf::Vector2f(WIDTH + 750, 550), sf::Vector2f(HALF));



    return set;
}

Set create_set_break() {
    Set set;
    sf::Texture ground_platform_texture;
    ground_platform_texture.loadFromFile("resources/ground_platform.png");

    set.add_platform(ground_platform_texture, sf::Vector2f(WIDTH, 600), sf::Vector2f(HALF));

    return set;
}

void spawn_set(std::vector<Set>& sets, int& spawned) {
    int set_choice;
    static int previous_choice;
    Set& last_set = sets.back();
    Platform& last_platform = last_set.platforms.back();

    auto limit = last_platform.getPosition().x + last_platform.getGlobalBounds().width;

    if (limit <= LIMIT) {

        if (spawned < 7) {
            do {
                set_choice = rand() % 5;
            } while (set_choice == previous_choice);

            previous_choice = set_choice;

            Set set;
            switch (set_choice)
            {
            case 0:
                set = create_set_1();
                sets.emplace_back(set);
                break;
            case 1:
                set = create_set_2();
                sets.emplace_back(set);
                break;
            default:
                break;
            }
            spawned++;
        }
        else {
            Set set = create_set_break();
            sets.emplace_back(set);
            spawned = 0;
        }
    }

}

void clear_set(std::vector<Set>& sets) {
    Set& first_set = sets.front();
    Platform& last_platform = first_set.platforms.back();

    if (last_platform.getPosition().x + last_platform.getGlobalBounds().width <= 0) {
        
    }
}

void set_init(std::vector<Set>& sets) {
    for (auto& set : sets) {
        for (size_t i = 0; i < set.platforms.size(); i++) {
            set.platforms[i].setTexture(set.platform_textures[i]);
        }
    }
}

void set_update(sf::Time& elapsed_time, sf::Time& progress_time, std::vector<Set>& sets, Player& player, float& velocity_progress) {
    progress_time += elapsed_time;


    if (progress_time.asSeconds() >= 10.0) {
        progress_time = sf::Time::Zero;
        velocity_progress -= 1.0;
    }
    set_init(sets);


    for (auto& set : sets) {
        float o_velocity = set.objects_velocity + velocity_progress;

        for (auto& platform : set.platforms) {
            platform.move(o_velocity * elapsed_time.asSeconds(), 0.0);
        }

    }
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
    bool end = false;
    float velocity_progress = 0;
    int spawned = 0;
    sf::Clock clock;
    sf::Time progress_time;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "PixelRunner");
    window.setFramerateLimit(60);

    // Create sets objects
    std::vector<Set> sets;
    Set starting_set = create_starting_set();
    sets.emplace_back(starting_set);

    // Create player
    Player player = create_player();

    //Game loop
    while (window.isOpen()) {
        sf::Time elapsed_time = clock.restart();
        over_borderline(player, window, end);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //Platform methods
        set_update(elapsed_time, progress_time, sets, player, velocity_progress);
        spawn_set(sets, spawned);
        clear_set(sets);

        //Player Methods
        player.movement(elapsed_time);
        player.update(elapsed_time, sets);

        window.clear(sf::Color::Black);

        for (auto& set : sets) {
            for (const auto& platform : set.platforms) {
                window.draw(platform);
            }

            
        }
        window.draw(player);
        window.display();
    }
    return 0;
}