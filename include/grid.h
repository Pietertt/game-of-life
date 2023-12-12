#pragma once

class Cell;

class Grid {

    public:
        Grid();
        void spawnGenerations(unsigned int screenWidth, unsigned int screenHeight);
        void populate();
        void swap();

        void calculateRuleOne();
        void calculateRuleTwo();
        void calculateRuleThree();
        void calculateRuleFour();

        Cell* getCurrentGen(int i, int j);
        Cell* getNextGen(int i, int j);

    private:
        Cell* currentGeneration [12][12];
        Cell* nextGeneration [12][12];

};
