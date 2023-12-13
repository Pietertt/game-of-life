#include <iostream>
#include "grid.h"
#include "cell.h"

Grid::Grid(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;

    for (int i = 0; i < this->rows; i++) {
        std::vector<Cell*> vector;
        for (int j = 0; j < this->columns; j++) {
            vector.push_back(NULL);
        }
        this->currentGeneration.push_back(vector);
    }

    for (int i = 0; i < this->rows; i++) {
        std::vector<Cell*> vector;
        for (int j = 0; j < this->columns; j++) {
            vector.push_back(NULL);
        }
        this->nextGeneration.push_back(vector);
    }
}

void Grid::spawnGenerations(unsigned int screenWidth, unsigned int screenHeight, int size) {    
    // Spawn the current generation
    for (int row = 1; row < this->rows; row++) {
        for (int position = 1; position < this->columns; position++) {
            Cell* cell = new Cell();
            cell->setX((position - 1) * size + 50);
            cell->setY((row - 1) * size + 50);
            cell->setSize(size);
            cell->setDead(true);

            this->currentGeneration.at(row).at(position) = cell;
        }
    }

    // Spawn the next generation
    for (int row = 1; row < this->rows; row++) {
        for (int position = 1; position < this->columns; position++) {
            Cell* cell = new Cell();
            cell->setX((position - 1) * size + 50);
            cell->setY((row - 1) * size + 50);
            cell->setSize(size);
            cell->setDead(true);

            this->nextGeneration.at(row).at(position) = cell;
        }
    }
}

void Grid::populate() {
    for (int row = 1; row < this->rows - 1; row++) {
        for (int position = 1; position < this->columns - 1; position++) {
            Cell* cell = this->currentGeneration.at(row).at(position);

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
}

void Grid::swap() {
     for (int row = 1; row < this->rows - 1; row++) {
        for (int position = 1; position < this->columns - 1; position++) {
            Cell* cell = this->getCurrentGen(row, position);

            bool deadState = this->getNextGen(row, position)->isDead();

            cell->setDead(deadState);
        }
    }
}

void Grid::calculateRules() {
    for (int row = 1; row < this->rows - 1; row++) {
        for (int position = 1; position < this->columns - 1; position++) {
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

Cell* Grid::getCurrentGen(int i, int j) {
    return this->currentGeneration.at(i).at(j);
}

Cell* Grid::getNextGen(int i, int j) {
    return this->nextGeneration.at(i).at(j);
}