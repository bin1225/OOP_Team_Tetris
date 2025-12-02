#include "LineClearItem.h"
#include <iostream>
// #include "Board.h"
// #include "Score.h"

using namespace std;

LineClearItem::LineClearItem()
    : Item("Line", "라인제거") {
}

bool LineClearItem::use(Board& board, Score& score, const Block& block) {
     int removed = board.removeTopLines(1);
     if (removed > 0) {
         score.addItemBonus(70);
         itemUI.highlightLine(removed);
         return true;
     }
     return false;
    return true;
}