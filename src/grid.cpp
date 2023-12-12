#include <iostream>
#include "grid.h"
#include "cell.h"

Grid::Grid() {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            this->currentGeneration[i][j] = NULL;
        }
    }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            this->nextGeneration[i][j] = NULL;
        }
    }
}

void Grid::spawnGenerations(unsigned int screenWidth, unsigned int screenHeight) {
    int size = (screenHeight / 10) - 10;

    // Spawn the current generation
    for (int row = 1; row < 11; row++) {
        for (int position = 1; position < 11; position++) {
            Cell* cell = new Cell();
            cell->setX((position - 1) * size + 50);
            cell->setY((row - 1) * size + 50);
            cell->setSize(size);
            cell->setDead(true);

            this->currentGeneration[row][position] = cell;
        }
    }

    // Spawn the next generation
    for (int row = 1; row < 11; row++) {
        for (int position = 1; position < 11; position++) {
            Cell* cell = new Cell();
            cell->setX((position - 1) * size + 50);
            cell->setY((row - 1) * size + 50);
            cell->setSize(size);
            cell->setDead(true);

            this->nextGeneration[row][position] = cell;
        }
    }
}

void Grid::populate() {
    for (int row = 1; row < 11; row++) {
        for (int position = 1; position < 11; position++) {
            Cell* cell = this->currentGeneration[row][position];

            cell->N__Neighbour = currentGeneration[row - 1][position];
            cell->NE_Neighbour = currentGeneration[row - 1][position + 1];
            cell->E__Neighbour = currentGeneration[row][position + 1];
            cell->SE_Neighbour = currentGeneration[row + 1][position + 1];
            cell->S__Neighbour = currentGeneration[row + 1][position];
            cell->SW_Neighbour = currentGeneration[row + 1][position - 1];
            cell->W__Neighbour = currentGeneration[row][position - 1];
            cell->NW_Neighbour = currentGeneration[row - 1][position - 1];

            cell->neighbours[0] = cell->N__Neighbour;
            cell->neighbours[1] = cell->NE_Neighbour;
            cell->neighbours[2] = cell->E__Neighbour;
            cell->neighbours[3] = cell->SE_Neighbour;
            cell->neighbours[4] = cell->S__Neighbour;
            cell->neighbours[5] = cell->SW_Neighbour;
            cell->neighbours[6] = cell->W__Neighbour;
            cell->neighbours[7] = cell->NW_Neighbour;
        }
    }

    this->currentGeneration[3][3]->setDead(false);
    this->currentGeneration[3][4]->setDead(false);
    this->currentGeneration[3][5]->setDead(false);
    this->currentGeneration[2][5]->setDead(false);
    this->currentGeneration[1][4]->setDead(false);

    this->nextGeneration[3][3]->setDead(false);
    this->nextGeneration[3][4]->setDead(false);
    this->nextGeneration[3][5]->setDead(false);
    this->nextGeneration[2][5]->setDead(false);
    this->nextGeneration[1][4]->setDead(false);
    // this->currentGeneration[3][2]->setDead(false);
    // this->currentGeneration[2][3]->setDead(false);
    // this->currentGeneration[2][4]->setDead(false);
    // this->currentGeneration[3][2]->setDead(false);
    // this->currentGeneration[3][3]->setDead(false);
}

void Grid::swap() {
     for (int row = 1; row < 11; row++) {
        for (int position = 1; position < 11; position++) {
            Cell* cell = this->getCurrentGen(row, position);

            bool deadState = this->getNextGen(row, position)->isDead();

            cell->setDead(deadState);
        }
    }
}

void Grid::calculateRuleOne() {
    for (int row = 1; row < 11; row++) {
        for (int position = 1; position < 11; position++) {
            Cell* currentGenCell = this->getCurrentGen(row, position);
            Cell* nextGenCell = this->getNextGen(row, position);

            int count = currentGenCell->getAliveNeighbourCount();

            // Any live cell with fewer than two live neighbours dies,
            // as if caused by underpopulation
            if (currentGenCell->isDead() == false) {
                if (count < 2) {
                    nextGenCell->setDead(true);
                }
            }

            // Any live cell with two or three live neighbours lives
            // on to the next generation
            if (currentGenCell->isDead() == false) {
                if (count == 2 || count == 3) {
                    nextGenCell->setDead(false);
                }
            }

            // Any live cell with more than three live neighbours dies,
            // as if by overpopulation
            if (currentGenCell->isDead() == false) {
                if (count >= 4) {
                    nextGenCell->setDead(true);
                }
            }

            // Any dead cell with exactly three live neighbours becomes a
            // live cell, as if by reproduction
            if (currentGenCell->isDead() == true) {
                if (count == 3) {
                    nextGenCell->setDead(false);
                }
            }
        }
    }
}

void Grid::calculateRuleTwo() {
    for (int row = 1; row < 11; row++) {
        for (int position = 1; position < 11; position++) {
            Cell* cell = this->getCurrentGen(row, position);

            int count = cell->getAliveNeighbourCount();

            // Any live cell with more than three live neighbours dies
            if (cell->isDead() == false) {
                if (count > 3) {
                    cell->setDead(true);
                }
            }
        }
    }
}

void Grid::calculateRuleThree() {
    for (int row = 1; row < 11; row++) {
        for (int position = 1; position < 11; position++) {
            Cell* cell = this->getCurrentGen(row, position);

            int count = cell->getAliveNeighbourCount();

            // Any live cell with two or three live neighbours lives,
            // unchanged, to the next generation.
            if (cell->isDead() == false) {
                if (count == 2 || count == 3) {
                    // cell->setDead(true);
                }
            }
        }
    }
}

void Grid::calculateRuleFour() {
    for (int row = 1; row < 11; row++) {
        for (int position = 1; position < 11; position++) {
            Cell* cell = this->getCurrentGen(row, position);

            int count = cell->getAliveNeighbourCount();

            // Any dead cell with exactly three live neighbours will come to life
            if (cell->isDead() == true) {
                if (count == 3) {
                    cell->setDead(false);
                }
            }
        }
    }
}

Cell* Grid::getCurrentGen(int i, int j) {
    return this->currentGeneration[i][j];
}

Cell* Grid::getNextGen(int i, int j) {
    return this->nextGeneration[i][j];
}