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

int Board::removeTopLines(int count) {
    int lastRemovedRow = -1;

    for (int i = 0; i < count; ++i) {

        // ---- 1) 삭제 대상 라인 탐색 ----
        int targetLine = -1;
        for (int y = 0; y < HEIGHT - 1; ++y) {
            for (int x = 1; x < WIDTH - 1; ++x) {
                if (grid[y][x] != 0) {
                    targetLine = y;
                    break;
                }
            }
            if (targetLine != -1) break;
        }

        // 삭제할 라인이 없으면 종료
        if (targetLine == -1)
            break;

        lastRemovedRow = targetLine;

        // ---- 2) 위의 라인을 아래로 한 칸씩 이동 ----
        for (int row = targetLine; row > 0; --row) {
            for (int col = 1; col < WIDTH - 1; ++col) {
                grid[row][col] = grid[row - 1][col];
            }
        }

        // ---- 3) 최상단 라인 비우기 ----
        for (int col = 1; col < WIDTH - 1; ++col) {
            grid[0][col] = 0;
        }
    }

    return lastRemovedRow;
}



int Board::blastArea(int centerX, int centerY, int radius) {
    int removed = 0;

    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            int bx = centerX + x;
            int by = centerY + y;

            // 원형 거리 계산
            if (x * x + y * y > radius * radius) continue;

            if (bx > 0 && bx < WIDTH - 1 && by >= 0 && by < HEIGHT - 1) {
                if (grid[by][bx] != 0) {
                    grid[by][bx] = 0;
                    removed++;
                }
            }
        }
    }

    // 중력 정리
    for (int x = 1; x < WIDTH - 1; x++) {
        for (int y = HEIGHT - 2; y >= 0; y--) {
            if (grid[y][x] != 0 && grid[y + 1][x] == 0) {
                int yy = y;
                while (yy + 1 < HEIGHT - 1 && grid[yy + 1][x] == 0) {
                    grid[yy + 1][x] = grid[yy][x];
                    grid[yy][x] = 0;
                    yy++;
                }
            }
        }
    }

    return removed;
}
