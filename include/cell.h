#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Cell {

    public:
        Cell();
        sf::RectangleShape getShape();
        float getX();
        void setX(float x);
        float getY();
        void setY(float y);

        float getSize();
        void setSize(float size);

        sf::Color getColor();
        void setColor(sf::Color color);

        bool isDead();
        void setDead(bool dead);

        int getAliveNeighbourCount();

        // NW  N  NE
        // W   .  E
        // SW  S  SE

        Cell* N__Neighbour = NULL;
        Cell* NE_Neighbour = NULL;
        Cell* E__Neighbour = NULL;
        Cell* SE_Neighbour = NULL;
        Cell* S__Neighbour = NULL;
        Cell* SW_Neighbour = NULL;
        Cell* W__Neighbour = NULL;
        Cell* NW_Neighbour = NULL;

    private:
        float x = 0;
        float y = 0;
        float size;
        sf::RectangleShape shape;
        bool dead;

};
