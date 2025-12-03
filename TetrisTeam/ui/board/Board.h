#pragma once
#include "../block/Block.h"
#include <vector>
using std::vector;

class Board {
public:
    static constexpr int WIDTH = 14;
    static constexpr int HEIGHT = 21;
private:
    vector<vector<int>> grid;
    int clearedLines = 0;
public:
    Board();
    ~Board() = default;
    bool checkCollision(const Block& block) const;
    void mergeBlock(const Block& block);
    int clearFullLines();
    void update() const;
    bool isOccupied(int x, int y) const;
    int getClearedLines() const;
    void reset();
    vector<vector<int>>& getGrid();
    int removeTopLines(int count);
    int removeBottomLines(int count);
    int blastArea(int centerX, int centerY, int radius);
};