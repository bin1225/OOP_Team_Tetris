#pragma once
#include <array>

class Block {
public:
    static constexpr int SIZE = 4;
    using ShapeMatrix = std::array<std::array<int, SIZE>, SIZE>;
private:
    int shape;
    int angle;
    int x;
    int y;
    int color;
    static const std::array<std::array<ShapeMatrix , 4>, 7> SHAPES;
public:
    Block();
    ~Block() = default;
    const ShapeMatrix& getShape() const;
    int getX() const;
    int getY() const;
    int getColor() const;
    int getAngle() const;
    int getType() const;
    void setPosition(int newX, int newY);

    void moveDown();
    void moveLeft();
    void moveRight();

    void rotateRight();
    void rotateLeft();

};

