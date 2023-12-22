#include <iostream>
#include <fstream>
#include <sstream>
#include "grid.h"
#include "cell.h"

Grid::Grid() {

}

std::string Grid::calculateDimensions(std::ifstream &input, int margin, int height, int width) {
    std::string lines;

    for (std::string line; getline( input, line );) {
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        line.erase(std::remove(line.begin(), line.end(), '!'), line.end());
        if (line[0] == '#') {
            continue;
        } else if (line[0] == 'x') {
            std::string x = "";
            std::string y = "";

            bool xLock = false;
            bool yLock = false;
            int xStamp = 0;
            int yStamp = 0;

            for (int i = 0; i < line.size(); i++) {
                if (line[i] == 'x') {
                    xLock = true;
                    xStamp = i;
                }

                if (xLock && line[i] == ',') {
                    xLock = false;
                }

                if (xLock && i > xStamp + 1) {
                    x += line[i];
                }

                if (line[i] == 'y') {
                    yLock = true;
                    yStamp = i;
                }

                if (yLock && line[i] == ',') {
                    yLock = false;
                }

                if (yLock && i > yStamp + 1) {
                    y += line[i];
                }
            }
            
            this->columns = stoi(x) + margin;
            this->rows = stoi(y) + margin;
            this->size = (height / columns);
            
        } else {
            lines += line;
        }
    }

    return lines;
}

void Grid::setDimensions() {
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

void Grid::spawnGenerations() {
    // Spawn the current generation
    for (int row = 0; row < this->rows; row++) {
        for (int position = 0; position < this->columns; position++) {
            Cell* cell = new Cell();
            cell->setX((position) * this->size + 50);
            cell->setY((row) * this->size + 50);
            cell->setSize(this->size);
            cell->setDead(true);

            this->currentGeneration.at(row).at(position) = cell;

            Cell* newGenCell = new Cell();
            newGenCell->setX((position) * this->size + 50);
            newGenCell->setY((row) * this->size + 50);
            newGenCell->setSize(this->size);
            newGenCell->setDead(true);

            this->nextGeneration.at(row).at(position) = newGenCell;
        }
    }
}

void Grid::populate() {
    for (int row = 0; row < this->rows; row++) {
        for (int position = 0; position < this->columns; position++) {

            Cell* cell = this->currentGeneration.at(row).at(position);
            Cell* nextGenCell = this->nextGeneration.at(row).at(position);

            // North
            if (row > 0) {
                cell->N__Neighbour =     this->currentGeneration.at(row - 1).at(position);
                nextGenCell->N__Neighbour = this->nextGeneration.at(row - 1).at(position);
            }

            // Northeast
            if (row > 0 && position < this->columns - 1) {
                cell->NE_Neighbour =     this->currentGeneration.at(row - 1).at(position + 1);
                nextGenCell->NE_Neighbour = this->nextGeneration.at(row - 1).at(position + 1);
            }

            // East
            if (position < this->columns - 1) {
                cell->E__Neighbour =     this->currentGeneration.at(row).at(position + 1);
                nextGenCell->E__Neighbour = this->nextGeneration.at(row).at(position + 1);
            }

            // Southeast
            if (row < this->rows - 1 && position < this->columns - 1) {
                cell->SE_Neighbour =     this->currentGeneration.at(row + 1).at(position + 1);
                nextGenCell->SE_Neighbour = this->nextGeneration.at(row + 1).at(position + 1);
            }

            // South
            if (row < (this->rows - 1)) {
                cell->S__Neighbour =     this->currentGeneration.at(row + 1).at(position);
                nextGenCell->S__Neighbour = this->nextGeneration.at(row + 1).at(position);
            }

            // Southwest
            if (position > 0 && row < this->rows - 1) {
                cell->SW_Neighbour =     this->currentGeneration.at(row + 1).at(position - 1);
                nextGenCell->SW_Neighbour = this->nextGeneration.at(row + 1).at(position - 1);
            }

            // West
            if (position > 0) {
                cell->W__Neighbour =     this->currentGeneration.at(row).at(position - 1);
                nextGenCell->W__Neighbour = this->nextGeneration.at(row).at(position - 1);
            }

            // Northwest
            if (row > 0 && position > 0) {
                cell->NW_Neighbour =     this->currentGeneration.at(row - 1).at(position - 1);
                nextGenCell->NW_Neighbour = this->nextGeneration.at(row - 1).at(position - 1);
            }
        }
    }
}

void Grid::setPattern(std::string lines, int margin) {
    std::stringstream ss(lines);
    std::string segment;
    std::vector<std::string> seglist;

    int currentRow = margin / 2;
    int currentPosition = margin / 2;

    while(std::getline(ss, segment, '$')) {
        currentPosition = margin / 2;
        char* characters = new char[segment.length() + 1];
        strcpy(characters, segment.c_str());

        for (int i = 0; i < strlen(characters); i++) {
            if (characters[i] == 'b') {
                // Single dead cell
                if (characters[i - 1] >= '0' && characters[i - 1] <= '9' ) {
                    continue;
                }
                this->getCurrentGen(currentRow, currentPosition)->setDead(true);
                this->getNextGen(currentRow, currentPosition)->setDead(true);
                currentPosition++;
            } else if (characters[i] == 'o') {
                // Single alive cell
                if (characters[i - 1] >= '0' && characters[i - 1] <= '9' ) {
                    continue;
                }
                this->getCurrentGen(currentRow, currentPosition)->setDead(false);
                this->getNextGen(currentRow, currentPosition)->setDead(false);
                currentPosition++;
            } else {
                // Multiple cells
                int number = 0;
                if (characters[i + 1] != 'o' || characters[i + 1] != 'b') {
                    char* numbers = new char[2];
                    numbers[0] = characters[i];
                    numbers[1] = characters[i + 1];
                    number = atoi(numbers);
                }

                char character;
                
                if (number > 9) {
                    character = characters[i + 2];
                } else {
                    character = characters[i + 1];
                }

                if (character == 'b') {
                    // // Multiple dead cells
                    for (int j = 0; j < number; j++) {
                        this->getCurrentGen(currentRow, currentPosition)->setDead(true);
                        this->getNextGen(currentRow, currentPosition)->setDead(true);
                        
                        currentPosition++;
                    }
                } else {
                    // Multiple alive cells
                    for (int j = 0; j < number; j++) {
                        
                        this->getCurrentGen(currentRow, currentPosition)->setDead(false);
                        this->getNextGen(currentRow, currentPosition)->setDead(false);
                        currentPosition++;
                    }
                }

                if (number > 9) {
                    i++;
                }
            }
        }

        currentRow++;
    }
}

void Grid::swap() {
     for (int row = 0; row < this->rows; row++) {
        for (int position = 0; position < this->columns; position++) {
            Cell* cell = this->getCurrentGen(row, position);

            bool deadState = this->getNextGen(row, position)->isDead();

            cell->setDead(deadState);
        }
    }
}

void Grid::calculateRules() {
    for (int row = 0; row < this->rows; row++) {
        for (int position = 0; position < this->columns; position++) {
        
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