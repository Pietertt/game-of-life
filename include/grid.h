#pragma once

#include <vector>

class Cell;

class Grid {

    public:
        Grid(int rows, int columns);
        void spawnGenerations(unsigned int screenWidth, unsigned int screenHeight, int size);
        void populate();
        void swap();

        void calculateRules();

        Cell* getCurrentGen(int i, int j);
        Cell* getNextGen(int i, int j);

        int rows;
        int columns;

    private:
        std::vector<std::vector<Cell*>> currentGeneration;
        std::vector<std::vector<Cell*>> nextGeneration;
     

};
