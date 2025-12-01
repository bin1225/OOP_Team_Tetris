#include "LineClearItem.h"
#include <iostream>
// #include "Board.h"
// #include "Score.h"

using namespace std;

LineClearItem::LineClearItem()
    : Item("Line", "라인제거") {
}

bool LineClearItem::use(Board& board, Score& score) {
     int removed = board.removeTopLines(1);
     if (removed) {
         score.addItemBonus(removed * 50);
         return true;
     }
     return false;
    return true;
}