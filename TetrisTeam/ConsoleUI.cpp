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

void ConsoleUI::SetColor(int color) {
    static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(std_output_handle, color);
}

void ConsoleUI::showGameOver() {
    system("cls");
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
            show_cur_block(rand() % 7, rand() % 4, 6, 14, 5, 1);
            show_cur_block(rand() % 7, rand() % 4, 12, 14, 5, 1);
            show_cur_block(rand() % 7, rand() % 4, 19, 14, 5, 1);
            show_cur_block(rand() % 7, rand() % 4, 24, 14, 5, 1);
        }
        if (_kbhit())
            break;
        Sleep(30);
    }

    _getche();
    system("cls");
}

int ConsoleUI::showLevelMenu() {
    int i = 0;
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


    while (i < 1 || i > 8) {
        gotoxy(10, 3);
        printf("Select Start level[1-8]:       \b\b\b\b\b\b\b");
        gotoxy(34, 3);

        if (!(cin >> i)) {
            cin.clear();
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            i = 0;
        }

        /*if (scanf_s("%d", &i) != 1) {
            while (getchar() != '\n') {}
            i = 0;
        }*/
    }
    system("cls");
    return i - 1;
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


void ConsoleUI::show_next_block(int shape, int level) {
    int i;
    SetColor(BLACK);
    for (i = 0; i < 8; i++) {
        gotoxy(33, i);
        printf("                ");
    }

    SetColor((level + 1) % 6 + 1);
    for (i = 1; i < 7; i++) {
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
    show_cur_block(shape, 0, 16, 1, 5, 1);
}

void ConsoleUI::show_cur_block(int shape, int angle, int x, int y, int ab_x, int ab_y) {
    switch (shape) {
    case 0:
        SetColor(RED);
        break;
    case 1:
        SetColor(BLUE);
        break;
    case 2:
        SetColor(SKY_BLUE);
        break;
    case 3:
        SetColor(WHITE);
        break;
    case 4:
        SetColor(YELLOW);
        break;
    case 5:
        SetColor(VIOLET);
        break;
    case 6:
    default:
        SetColor(GREEN);
        break;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j + y < 0)
                continue;

            if (block[shape][angle][j][i] == 1) {
                gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
                printf("■");
            }
        }
    }
    SetColor(BLACK);
    gotoxy(77, 23);
}

void ConsoleUI::erase_cur_block(int shape, int angle, int x, int y, int ab_x, int ab_y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block[shape][angle][j][i] == 1) {
                gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
                printf("  ");
                //break;
            }
        }
    }
}

void ConsoleUI::show_total_block(char total_block[21][14], int level, int ab_x, int ab_y) {
    SetColor(DARK_GRAY);
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 14; j++) {
            if (j == 0 || j == 13 || i == 20) //레벨에 따라 외벽 색이 변함
            {
                SetColor((level % 6) + 1);
            }
            else {
                SetColor(DARK_GRAY);
            }
            gotoxy((j * 2) + ab_x, i + ab_y);
            if (total_block[i][j] == 1) {
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