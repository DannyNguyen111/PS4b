// Copyright 2025 Danny Nguyen
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AniPlayer.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <json_file>\n";
        return 1;
    }

    std::string jsonFile = argv[1];
    AP::AniPlayer player(jsonFile);

    sf::RenderWindow window(sf::VideoMode(player.pixelWidth(), player.pixelHeight()), jsonFile);
    sf::Time initialTime = sf::Time::Zero;
    std::cout << ">>> Forcing draw at t = " << initialTime.asSeconds() << "s <<<\n";

    player.setTime(0.0f);
    window.clear(sf::Color::Transparent);
    window.draw(player);
    window.display();
    sf::Clock clock;
    bool paused = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    player.restart();
                    clock.restart();
                    player.tween(sf::Time::Zero);
                }
                if (event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Space) {
                    paused = !paused;
                    player.togglePause();
                }
            }
        }

        if (!paused) {
            player.tween(clock.getElapsedTime());
        }

        window.clear(sf::Color::Transparent);
        window.draw(player);
        window.display();
    }

    return 0;
}

