#pragma once
#include "../block/Block.h"
#include <vector>

class Board {
public:
    static constexpr int WIDTH = 14;
    static constexpr int HEIGHT = 21;
private:
    std::vector<std::vector<int>> grid;
    int clearedLines = 0;
public:
    Board();
    ~Board() = default;
    bool checkCollision(const Block& block) const;
    void mergeBlock(const Block& block);
    int clearFullLines();
    void update();
    bool isOccupied(int x, int y) const;
    int getClearedLines() const;
    void reset();
};