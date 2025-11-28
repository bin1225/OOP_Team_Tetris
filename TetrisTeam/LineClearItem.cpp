#include "LineClearItem.h"
#include <iostream>
// #include "Board.h"
// #include "Score.h"

using namespace std;

LineClearItem::LineClearItem()
    : Item("Line Clear", "Remove the top line") {
}

bool LineClearItem::use(Board& board, Score& score) {
    // TODO: Board 클래스의 removeTopLine() 메서드 호출
    // bool success = board.removeTopLine();
    // if (success) {
    //     score.addItemBonus(50);
    //     return true;
    // }
    // return false;
    cout << "LineClearItem used: Top line cleared!" << endl;
    return true;
}