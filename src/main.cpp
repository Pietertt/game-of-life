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

int main(int argc, char** argv) {
    auto mainDisplayId = CGMainDisplayID();
    unsigned int width = CGDisplayPixelsWide(mainDisplayId);
    unsigned int height = CGDisplayPixelsHigh(mainDisplayId) - 22;

    auto window = sf::RenderWindow{ { width, height }, "Conway's Game of Life" };
    window.setFramerateLimit(144);

    int count = 0;
    int rows = 0;
    int columns = 0;

    Grid* grid = NULL;

    if (argv[1] == "random") {

    } else {
        std::string filename = "templates/";
        filename += argv[1];

        std::ifstream input(filename);

        for (std::string line; getline( input, line );) {
            if (count == 0) {
                rows = std::stoi(line.substr(0, line.find(",")));
                columns = std::stoi(line.substr(0, line.find(",")));

                rows = rows + 2;
                columns = columns + 2;

                int size = (height / columns);

                grid = new Grid(rows, columns);
                grid->spawnGenerations(width, height, size);
                grid->populate();
            } else {
                line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
                std::stringstream ss(line);
                std::string segment;
                std::vector<int> seglist;

                while(std::getline(ss, segment, ',')) {
                    seglist.push_back(std::stoi(segment));
                }

                for (int i = 1; i < seglist.size(); i++) {
                    grid->getCurrentGen(count, i)->setDead(!seglist.at(i));
                }
            }
            count++;
        };
    }

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        for (int i = 1; i < rows - 1; i++) {
            for (int j = 1; j < columns - 1; j++) {
                window.draw(grid->getCurrentGen(i, j)->getShape());
            }
        }

        window.display();

        grid->calculateRules();
        grid->swap();

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}
