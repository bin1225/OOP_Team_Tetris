#pragma once
#include "ConsoleUI.h"
#include "../ui/Block/Block.h"
#include "../ui/board/Board.h"
#include "../core/GameConstants.h"

class ItemUI {
private:

public:

    int gotoxy(int x, int y);
    void SetColor(int color);
    // 시각 효과
    void flashArea(int x, int y, int radius);
    void highlightLine(int row);
};
