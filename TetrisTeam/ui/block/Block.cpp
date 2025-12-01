#include "Block.h"
#include <cstdlib>

Block::Block(const int type, const int startX = 5, const int startY = -3) : shape(type), angle(0), x(startX), y(startY),
                                                                   color(type + 9) {
}

const Block::ShapeMatrix &Block::getShape() const {
    return SHAPES[shape][angle];
}

int Block::getX() const {
    return x;
}

int Block::getY() const {
    return y;
}

int Block::getColor() const {
    return color;
}

int Block::getType() const {
    return shape;
}

int Block::getAngle() const {
    return angle;
}

void Block::setPosition(const int newX, const int newY) {
    x = newX;
    y = newY;
}

void Block::moveLeft() {
    --x;
}

void Block::moveRight() {
    ++x;
}

void Block::moveDown() {
    ++y;
}

void Block::rotateLeft() {
    angle = (angle + 1) % 4;
}

void Block::rotateRight() {
    angle = (angle + 3) % 4;
}

Block Block::createBlock() {
    const int type = rand() % 7;
    return Block(type);
}

Block Block::rotateBlock() const {
    Block temp = *this;
    temp.rotateRight();
    return temp;
}
