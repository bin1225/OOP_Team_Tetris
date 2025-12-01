#include "LineClearItem.h"
#include <iostream>
// #include "Board.h"
// #include "Score.h"

using namespace std;

LineClearItem::LineClearItem()
    : Item("Line Clear", "Remove the top line") {
}

bool LineClearItem::use(Board& board, Score& score) {
    // TODO: Board Ŭ������ removeTopLine() �޼��� ȣ��
    // bool success = board.removeTopLine();
    // if (success) {
    //     score.addItemBonus(50);
    //     return true;
    // }
    // return false;
    cout << "LineClearItem used: Top line cleared!" << endl;
    return true;
}