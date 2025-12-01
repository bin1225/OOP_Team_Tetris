#include "Board.h"
#include "../block/Block.h"
#include <iostream>
using namespace std;

Board::Board() {
    grid.assign(HEIGHT, std::vector<int>(WIDTH, 0));

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (x == 0 || x == WIDTH - 1 || y == HEIGHT - 1) {
                grid[y][x] = 1; // 벽과 바닥 표시
            }
        }
    }
}

bool Board::checkCollision(const Block &block) const {
    const auto& shape = block.getShape();
    const int bx = block.getX();
    const int by = block.getY();

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (shape[i][j] != 0) {
                const int boardX = bx + j;
                const int boardY = by + i;

                if (boardX < 0 || boardX >= WIDTH || boardY >= HEIGHT)
                    return true;

                if (boardY >= 0 && grid[boardY][boardX] != 0)
                    return true;
            }
        }
    }
    return false;
}

void Board::mergeBlock(const Block &block) {
    const auto& shape = block.getShape();
    const int bx = block.getX();
    const int by = block.getY();

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (shape[i][j] != 0) {
                const int boardX = bx + j;
                const int boardY = by + i;

                if (boardY >= 0 && boardY < HEIGHT && boardX >= 0 && boardX < WIDTH) {
                    grid[boardY][boardX] = shape[i][j];
                }
            }
        }
    }
}

int Board::clearFullLines() {
    int linesCleared = 0;

    for (int y = 0; y < HEIGHT - 1; ++y) {
        bool isFull = true;
        for (int x = 1; x < WIDTH - 1; ++x) {
            if (grid[y][x] == 0) {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            linesCleared++;
            for (int row = y; row > 0; --row)
                for (int col = 1; col < WIDTH - 1; ++col)
                    grid[row][col] = grid[row - 1][col];

            for (int col = 0; col < WIDTH; ++col)
                grid[0][col] = (col == 0 || col == WIDTH - 1) ? 1 : 0;

            --y;
        }
    }

    clearedLines += linesCleared;
    return linesCleared;
}

void Board::update() const {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (grid[y][x] == 1)
                cout << "■";
            else
                cout << "  ";
        }
        cout << endl;
    }
}

int Board::getClearedLines() const {
    return clearedLines;
}

bool Board::isOccupied(int x, int y) const {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return true;
    return grid[y][x] == 1;
}

void Board::reset() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (x == 0 || x == WIDTH - 1 || y == HEIGHT - 1)
                grid[y][x] = 1;
            else
                grid[y][x] = 0;
        }
    }
    clearedLines = 0;
}

vector<vector<int>>& Board::getGrid() {
    return grid;
}