#include "ItemUI.h"
#include <Windows.h>
#include <thread>
#include "../ui/board/Board.h"

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

                // 보드 내부(벽/바닥 제외)만 적용
                if (px <= 0 || px >= Board::WIDTH - 1) continue;
                if (py < 0 || py >= Board::HEIGHT - 1) continue;

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

                // 보드 내부 범위 체크 동일하게
                if (px <= 0 || px >= Board::WIDTH - 1) continue;
                if (py < 0 || py >= Board::HEIGHT - 1) continue;

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
    // 보드 내부 라인만 처리 (바닥 제외)
    if (row < 0 || row >= Board::HEIGHT - 1) return;

    // 깜빡이면서 라인 제거 효과
    for (int i = 0; i < 3; i++)
    {
        SetColor(YELLOW);
        for (int col = 1; col < Board::WIDTH - 1; col++) {
            gotoxy(col * 2 + 5, row + 1);
            printf("■■");
        }
        Sleep(80);

        SetColor(BLACK);
        for (int col = 1; col < Board::WIDTH - 1; col++) {
            gotoxy(col * 2 + 5, row + 1);
            printf("  ");
        }
        Sleep(50);
    }
}

