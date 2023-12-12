#include <SFML/Graphics.hpp>
#include "cell.h"

Cell::Cell() {
    this->shape.setFillColor(sf::Color::White);
}

sf::RectangleShape Cell::getShape() {
    return this->shape;
}

float Cell::getX() {
    return this->x;
}

void Cell::setX(float x) {
    this->x = x;
    this->shape.setPosition(this->getX(), this->getY());
}

float Cell::getY() {
    return this->y;
}

void Cell::setY(float y) {
    this->y = y;
    this->shape.setPosition(this->getX(), this->getY());
}

float Cell::getSize() {
    return this->size;
}

void Cell::setSize(float size) {
    this->size = size;
    this->shape.setSize(sf::Vector2f(this->getSize(), this->getSize()));
    // this->shape.setOrigin(this->shape.getSize().x / 2, this->shape.getSize().y / 2);
}

sf::Color Cell::getColor() {
    return this->shape.getFillColor();
}

void Cell::setColor(sf::Color color) {
    this->shape.setFillColor(color);
}

bool Cell::isDead() {
    return this->dead;
}

void Cell::setDead(bool dead) {
    if (dead) {
        this->setColor(sf::Color::White);
    } else {
        this->setColor(sf::Color::Black);
    }
    this->dead = dead;
}

int Cell::getAliveNeighbourCount() {
    int count = 0;

    if (this->N__Neighbour && !this->N__Neighbour->isDead()) count++;
    if (this->NE_Neighbour && !this->NE_Neighbour->isDead()) count++;
    if (this->E__Neighbour && !this->E__Neighbour->isDead()) count++;
    if (this->SE_Neighbour && !this->SE_Neighbour->isDead()) count++;
    if (this->S__Neighbour && !this->S__Neighbour->isDead()) count++;
    if (this->SW_Neighbour && !this->SW_Neighbour->isDead()) count++;
    if (this->W__Neighbour && !this->W__Neighbour->isDead()) count++;
    if (this->NW_Neighbour && !this->NW_Neighbour->isDead()) count++;

    return count;
}