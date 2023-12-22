#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <CoreGraphics/CGDisplayConfiguration.h>
#include <chrono>
#include <thread>
#include "cell.h"
#include "grid.h"
#include <ctype.h>

int main(int argc, char** argv) {
    auto mainDisplayId = CGMainDisplayID();
    unsigned int width = CGDisplayPixelsWide(mainDisplayId);
    unsigned int height = CGDisplayPixelsHigh(mainDisplayId) - 22;

    auto window = sf::RenderWindow{ { width, height }, "Conway's Game of Life" };
    window.setFramerateLimit(144);

    int count = 0;
    int rows = 0;
    int columns = 0;

    Grid* grid = new Grid();

    int margin = 30;

    std::ifstream input("templates/gosperglidergun.rle");

    std::string lines;

    lines = grid->calculateDimensions(input, margin, height, width);
    grid->setDimensions();
    grid->spawnGenerations();
    grid->populate();
    grid->setPattern(lines, margin);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < grid->rows; i++) {
            for (int j = 0; j < grid->columns; j++) {
                window.draw(grid->getCurrentGen(i, j)->getShape());
            }
        }

        window.display();

        grid->calculateRules();
        grid->swap();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
