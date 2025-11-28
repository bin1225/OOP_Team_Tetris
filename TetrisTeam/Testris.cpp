#include <cstdio>
#include <conio.h>
#include <cstring>
#include <Windows.h>
#include <ctime>
#include <iostream>
#include <limits>
#include "ConsoleUI.h"
#include "GameController.h"
#include "GameConstants.h"
#include "StructureTypes.h"

using namespace std;

//*********************************
//전역변수선언 -> GameController
//*********************************
//int level;
//int ab_x, ab_y; //화면중 블럭이 나타나는 좌표의 절대위치
//int block_shape, block_angle, block_x, block_y;
//int next_block_shape;
//int score;
//int lines;
//char total_block[21][14]; //화면에 표시되는 블럭들
//struct STAGE stage_data[10];
char block[7][4][4][4] = {
    //막대모양
    1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
    0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    //네모모양
    1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    //'ㅓ' 모양
    0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    //'ㄱ'모양
    1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
    0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    //'ㄴ' 모양
    1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,
    0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    //'Z' 모양
    1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,

    //'S' 모양
    0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0

};

//*********************************
//함수 선언
//*********************************

int make_new_block(); //return값으로 block의 모양번호를 알려줌
int strike_check(int shape, int angle, int x, int y); //블럭이 화면 맨 아래에 부닥쳤는지 검사 부닥치면 1을리턴 아니면 0리턴
int merge_block(int shape, int angle, int x, int y); //블럭이 바닥에 닿았을때 진행중인 블럭과 쌓아진 블럭을 합침
int block_start(int shape, int *angle, int *x, int *y); //블럭이 처음 나올때 위치와 모양을 알려줌
int move_block(int *shape, int *angle, int *x, int *y, int *next_shape); //게임오버는 1을리턴 바닥에 블럭이 닿으면 2를 리턴
int rotate_block(int shape, int *angle, int *x, int *y);
int check_full_line();

int main() {
    GameController game;
    game.run();
    return 0;
}




int make_new_block() {
    const int i = rand() % 100;
    if (i <= stage_data[level].stick_rate) //막대기 나올확률 계산
        return 0; //막대기 모양으로 리턴

    return rand() % 6 + 1;
}

int strike_check(int shape, int angle, int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // 블록이 실제로 존재하는 칸만 검사
            if (block[shape][angle][i][j] == 1) {
                int check_x = x + j;
                int check_y = y + i;

                // 좌우 벽 충돌 검사
                if (check_x <= 0 || check_x >= 13) {
                    return 1;
                }

                // 화면 위쪽은 충돌 검사 제외 (블록 생성 공간)
                if (check_y < 0) {
                    continue;
                }

                // 바닥 초과 검사
                if (check_y >= 21) {
                    return 1;
                }

                // 다른 블록과의 충돌 검사
                if (total_block[check_y][check_x] == 1) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int merge_block(int shape, int angle, int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (total_block[y + i][x + j] == 1) continue;
            total_block[y + i][x + j] |= block[shape][angle][i][j];
        }
    }
    check_full_line();
    show_total_block();

    return 0;
}

int block_start(int shape, int *angle, int *x, int *y) {
    *x = 5;
    *y = -3;
    *angle = 0;

    return 0;
}

int move_block(int* shape, int* angle, int* x, int* y, int* next_shape) {
    erase_cur_block(*shape, *angle, *x, *y);
    (*y)++; //블럭을 한칸 아래로 내림

    if (strike_check(*shape, *angle, *x, *y) == 1) {
        (*y)--; // 원위치

        // 게임 오버 판정: 블록이 화면 위쪽(y=0 이상)에서 고정될 때
        if (*y <= 0) {
            return 1; // 게임오버
        }

        merge_block(*shape, *angle, *x, *y);
        *shape = *next_shape;
        *next_shape = make_new_block();
        block_start(*shape, angle, x, y);
        show_next_block(*next_shape);
        return 2;
    }
    return 0;
}

int rotate_block(int shape, int *angle, int *x, int *y) {
    *angle = (*angle + 1) % 4;
    return 0;
}

int check_full_line() {
    int j;
    for (int i = 0; i < 20; i++) {
        for (j = 1; j < 13; j++) {
            if (total_block[i][j] == 0)
                break;
        }
        if (j == 13) //한줄이 다 채워졌음
        {
            lines++;
            show_total_block();
            SetColor(BLUE);
            gotoxy(1 * 2 + ab_x, i + ab_y);
            for (j = 1; j < 13; j++) {
                printf("□");
                Sleep(10);
            }
            gotoxy(1 * 2 + ab_x, i + ab_y);
            for (j = 1; j < 13; j++) {
                printf("  ");
                Sleep(10);
            }

            for (int k = i; k > 0; k--) {
                for (j = 1; j < 13; j++)
                    total_block[k][j] = total_block[k - 1][j];
            }
            for (j = 1; j < 13; j++)
                total_block[0][j] = 0;
            score += 100 + (level * 10) + (rand() % 10);
            show_gamestat();

            i--; // 확인요망
        }
    }
    return 0;
}



