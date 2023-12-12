#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <CoreGraphics/CGDisplayConfiguration.h>
#include <chrono>
#include <thread>
#include "cell.h"
#include "grid.h"

int main() {
    auto mainDisplayId = CGMainDisplayID();
    unsigned int width = CGDisplayPixelsWide(mainDisplayId);
    unsigned int height = CGDisplayPixelsHigh(mainDisplayId) - 22;

    auto window = sf::RenderWindow{ { width, height }, "Conway's Game of Life" };
    window.setFramerateLimit(144);

    Grid* grid = new Grid();
    grid->spawnGenerations(width, height);
    grid->populate();

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        

        window.clear(sf::Color::White);

        for (int i = 1; i < 11; i++) {
            for (int j = 1; j < 11; j++) {
                window.draw(grid->getCurrentGen(i, j)->getShape());
            }
        }

        window.display();

        grid->calculateRuleOne();
        grid->swap();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
