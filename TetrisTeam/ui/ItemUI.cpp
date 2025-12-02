#include "ItemUI.h"
#include <Windows.h>
#include <thread>


void ItemUI::SetColor(int color) {
    static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(std_output_handle, color);
}

int ItemUI::gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    if (x < 0) x = -x;
    if (y < 0) y = -y;
    pos.Y = static_cast<short>(y);
    pos.X = static_cast<short>(x);
    SetConsoleCursorPosition(hConsole, pos);
    return 0;
}

void ItemUI::flashArea(int x, int y, int radius)
{
    // 반짝이는 효과 3번 반복
    for (int cycle = 0; cycle < 3; cycle++)
    {
        SetColor(RED);
        for (int dy = -radius; dy <= radius; dy++) {
            for (int dx = -radius; dx <= radius; dx++) {

                int px = x + dx;
                int py = y + dy;

                if (dx * dx + dy * dy <= radius * radius) {
                    gotoxy(px * 2 + 5, py + 1);
                    printf("★");
                }
            }
        }
        Sleep(80);

        // 지우고 반짝임 유지
        SetColor(BLACK);
        for (int dy = -radius; dy <= radius; dy++) {
            for (int dx = -radius; dx <= radius; dx++) {

                int px = x + dx;
                int py = y + dy;

                if (dx * dx + dy * dy <= radius * radius) {
                    gotoxy(px * 2 + 5, py + 1);
                    printf("  ");
                }
            }
        }
        Sleep(50);
    }
}


void ItemUI::highlightLine(int row)
{
    // 깜빡이면서 라인 제거 효과
    for (int i = 0; i < 3; i++)
    {
        SetColor(YELLOW);
        for (int col = 1; col < 13; col++) {
            gotoxy(col * 2 + 5, row + 1);
            printf("■■");
        }
        Sleep(80);

        SetColor(BLACK);
        for (int col = 1; col < 13; col++) {
            gotoxy(col * 2 + 5, row + 1);
            printf("  ");
        }
        Sleep(50);
    }
}
