#include "ConsoleUI.h"
#include "board/Board.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int ConsoleUI::gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    if (x < 0) x = -x;
    if (y < 0) y = -y;
    pos.Y = static_cast<short>(y);
    pos.X = static_cast<short>(x);
    SetConsoleCursorPosition(hConsole, pos);
    return 0;
}

void ConsoleUI::SetColor(int color) {
    static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(std_output_handle, color);
}

void ConsoleUI::setCursorVisible(bool visible) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = visible; // true: 보이게, false: 안보이게
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void ConsoleUI::showGameOver() {
    system("cls");
    setCursorVisible(false);
    SetColor(RED);
    gotoxy(15, 8);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    gotoxy(15, 9);
    printf("┃**************************┃");
    gotoxy(15, 10);
    printf("┃*        GAME OVER       *┃");
    gotoxy(15, 11);
    printf("┃**************************┃");
    gotoxy(15, 12);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
    fflush(stdin);
    Sleep(1000);

    _getche();
    system("cls");
}

void ConsoleUI::showLogo() {
    setCursorVisible(false);
    gotoxy(21, 3);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    Sleep(100);
    gotoxy(21, 4);
    printf("┃◆◆◆◆◆ ◆◆◆◆ ◆◆◆◆◆ ◆◆   ◆◆◆ ◆◆◆ ┃");
    Sleep(100);
    gotoxy(21, 5);
    printf("┃  ◆   ◆      ◆   ◆ ◆   ◆  ◆   ┃");
    Sleep(100);
    gotoxy(21, 6);
    printf("┃  ◆   ◆◆◆◆   ◆   ◆◆    ◆  ◆◆◆ ┃");
    Sleep(100);
    gotoxy(21, 7);
    printf("┃  ◆   ◆      ◆   ◆ ◆   ◆    ◆ ┃");
    Sleep(100);
    gotoxy(21, 8);
    printf("┃  ◆   ◆◆◆◆   ◆   ◆  ◆ ◆◆◆ ◆◆◆ ┃");
    Sleep(100);
    gotoxy(21, 9);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

    gotoxy(26, 20);
    printf("Please Press Any Key~!");

    for (int i = 0; i >= 0; i++) {
        if (i % 40 == 0) {
            for (int j = 0; j < 5; j++) {
                gotoxy(17, 14 + j); // 18->17
                printf("                                                          ");
            }

            Block b1 = Block::createBlock();
            Block b2 = Block::createBlock();
            Block b3 = Block::createBlock();
            Block b4 = Block::createBlock();

            b1.setPosition(6, 14);
            b2.setPosition(12, 14);
            b3.setPosition(19, 14);
            b4.setPosition(24, 14);

            showCurrent(b1, 5, 1);
            showCurrent(b2, 5, 1);
            showCurrent(b3, 5, 1);
            showCurrent(b4, 5, 1);
        }
        if (_kbhit()) break;
        Sleep(30);
    }

    _getche();
    system("cls");
}

int ConsoleUI::showLevelMenu() {
    int i = 0;
    string input;

    setCursorVisible(false);
    SetColor(GRAY);
    gotoxy(10, 7);
    printf("┏━━━━━━━━━<GAME KEY>━━━━━━━━━┓");
    Sleep(10);
    gotoxy(10, 8);
    printf("┃ UP   : Rotate Block        ┃");
    Sleep(10);
    gotoxy(10, 9);
    printf("┃ DOWN : Move One-Step Down  ┃");
    Sleep(10);
    gotoxy(10, 10);
    printf("┃ SPACE: Move Bottom Down    ┃");
    Sleep(10);
    gotoxy(10, 11);
    printf("┃ LEFT : Move Left           ┃");
    Sleep(10);
    gotoxy(10, 12);
    printf("┃ RIGHT: Move Right          ┃");
    Sleep(10);
    gotoxy(10, 13);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

    setCursorVisible(true);
    while (true) {
        gotoxy(10, 3);
        SetColor(WHITE);
        printf("Select Start level[1-8]:       \b\b\b\b\b\b\b");
        gotoxy(34, 3);

        getline(cin, input);

        if (input.length() == 1 && input[0] >= '1' && input[0] <= '8') {
            setCursorVisible(false);
            system("cls");
            return (input[0] - '0') - 1;
        }

        // 잘못된 입력 지우기
        gotoxy(34, 3);
        for (size_t k = 0; k < input.length(); ++k) {
            printf(" ");
        }
    }
}

void ConsoleUI::showGameStat(int level, int score, int lines, int clear_line) {
    static int printed_text = 0;
    SetColor(GRAY);
    if (printed_text == 0) {
        gotoxy(35, 8);
        printf("STAGE");

        gotoxy(35, 10);
        printf("SCORE");

        gotoxy(35, 13);
        printf("LINES");
    }

    //int remain_lines = stage_data[level].clear_line - lines;
    int remain_lines = clear_line - lines;
    if (remain_lines < 0)
        remain_lines = 0;

    gotoxy(41, 8);
    printf("%d", level + 1);
    gotoxy(35, 11);
    printf("%10d", score);
    gotoxy(35, 14);
    printf("%10d", remain_lines);
}


void ConsoleUI::showNext(const Block& block, int level) {
    SetColor(BLACK);

    for (int i = 0; i < 8; i++) {
        gotoxy(33, i);
        printf("                ");
    }

    SetColor((level + 1) % 6 + 1);

    for (int i = 1; i < 7; i++) {
        gotoxy(33, i);
        for (int j = 0; j < 6; j++) {
            if (i == 1 || i == 6 || j == 0 || j == 5) {
                printf("■ ");
            }
            else {
                printf("  ");
            }
        }
    }

    Block b = block;
    b.setPosition(16, 1);
    showCurrent(b, 5, 1);
}

void ConsoleUI::showCurrent(const Block& block, int ab_x, int ab_y) {
    switch (block.getType()) {
    case 0: SetColor(RED); break;
    case 1: SetColor(BLUE); break;
    case 2: SetColor(SKY_BLUE); break;
    case 3: SetColor(WHITE); break;
    case 4: SetColor(YELLOW); break;
    case 5: SetColor(VIOLET); break;
    case 6:
    default: SetColor(GREEN); break;
    }

    const auto& shape = block.getShape();
    int x = block.getX();
    int y = block.getY();

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] == 0) continue;
            if (y + i < 0) continue;

            gotoxy((x + j) * 2 + ab_x, (y + i) + ab_y);
            printf("■");
        }
    }
    SetColor(BLACK);
    gotoxy(77, 23);
}

void ConsoleUI::eraseCurrent(const Block& block, int ab_x, int ab_y) {
    const auto& shape = block.getShape();
    int x = block.getX();
    int y = block.getY();

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] == 0) continue;
            if (y + i < 0) continue;

            gotoxy((x + j) * 2 + ab_x, (y + i) + ab_y);
            printf("  ");
        }
    }
}

void ConsoleUI::showTotal(const vector<vector<int>>& grid, int level, int ab_x, int ab_y) {
    SetColor(DARK_GRAY);
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 14; j++) {
            if (j == 0 || j == 13 || i == 20) //레벨에 따라 외벽 색이 변함
                SetColor((level % 6) + 1);
            else
                SetColor(DARK_GRAY);

            gotoxy((j * 2) + ab_x, i + ab_y);
            if (grid[i][j] == 1) {
                printf("■");
            }
            else {
                printf("  ");
            }
        }
    }
    SetColor(BLACK);
    gotoxy(77, 23);
}


void ConsoleUI::showItemStatus(const std::string& itemName, const std::string& itemDesc)
{
    const int x = 33;
    const int y = 17;
    const int width = 10;  // 내부 공간 기준

    // 색상 설정
    SetColor(YELLOW);

    // ┌───────────────┐
    gotoxy(x, y);
    printf("┌");
    for (int i = 0; i < width; i++) printf("─");
    printf("┐");

    // │      ITEM      │  ← 중앙 정렬
    std::string title = "ITEM";
    int padding = (width - static_cast<int>(title.length())) / 2;

    gotoxy(x, y + 1);
    printf("│");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", title.c_str());
    for (int i = 0; i < width - padding - title.length(); i++) printf(" ");
    printf("│");

    // 두 줄 공백
    gotoxy(x, y + 2);
    printf("│");
    for (int i = 0; i < width; i++) printf(" ");
    printf("│");

    gotoxy(x, y + 3);
    printf("│");
    for (int i = 0; i < width; i++) printf(" ");
    printf("│");

    // └───────────────┘
    gotoxy(x, y + 4);
    printf("└");
    for (int i = 0; i < width; i++) printf("─");
    printf("┘");


    // 내용 출력
    if (itemName.empty()) {
        SetColor(GRAY);
        gotoxy(x + 2, y + 2);
        printf("No Item");
        return;
    }

    // 아이템 있을 때
    SetColor(GREEN);
    gotoxy(x + 2, y + 2);
    printf("★ %s", itemName.c_str());

    SetColor(WHITE);
    gotoxy(x + 2, y + 3);
    printf("%s", itemDesc.c_str());
}

void ConsoleUI::showBlastEffect(int centerX, int centerY, int radius) {

    SetColor(RED);

    for (int r = 1; r <= radius; r++) {
        for (int y = -r; y <= r; ++y) {
            for (int x = -r; x <= r; ++x) {
                if (x * x + y * y <= r * r) {
                    gotoxy((centerX + x) * 2, centerY + y);
                    printf("%c", '*');
                }
            }
        }

        Sleep(40);

        // 지우기
        for (int y = -r; y <= r; ++y) {
            for (int x = -r; x <= r; ++x) {
                if (x * x + y * y <= r * r) {
                    gotoxy((centerX + x) * 2, centerY + y);
                    printf(" ");
                }
            }
        }
    }

    SetColor(BLACK);
}
