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

        Cell* N__Neighbour;
        Cell* NE_Neighbour;
        Cell* E__Neighbour;
        Cell* SE_Neighbour;
        Cell* S__Neighbour;
        Cell* SW_Neighbour;
        Cell* W__Neighbour;
        Cell* NW_Neighbour;

        Cell* neighbours[8];

    private:
        float x;
        float y;
        float size;
        sf::RectangleShape shape;
        bool dead;

};
