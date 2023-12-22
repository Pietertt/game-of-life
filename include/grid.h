#pragma once

#include <vector>

class Cell;

class Grid {

    public:
        Grid();
        std::string calculateDimensions(std::ifstream &input, int margin, int height, int width);
        void setDimensions();
        void spawnGenerations();
        void populate();
        void setPattern(std::string lines, int margin);
        void swap();

        void calculateRules();

        Cell* getCurrentGen(int i, int j);
        Cell* getNextGen(int i, int j);

        int rows;
        int columns;
        int size;

    private:
        std::vector<std::vector<Cell*>> currentGeneration;
        std::vector<std::vector<Cell*>> nextGeneration;
     

};
