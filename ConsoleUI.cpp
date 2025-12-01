#include "ConsoleUI.h"

int ConsoleUI::gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    if (x < 0)
        x = -x;
    if (y < 0)
        y = -y;
    pos.Y = static_cast<short>(y);
    pos.X = static_cast<short>(x);
    SetConsoleCursorPosition(hConsole, pos);
    return 0;
}