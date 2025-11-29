#pragma once
#include <cstdio>
#include <conio.h>
#include <cstring>
#include <Windows.h>
#include <ctime>
#include <iostream>
#include <limits>
#include "Board.h"
#include "Score.h"
#include "Ranking.h"
#include "ConsoleUI.h"

class GameController
{
    // ui 객체
    ConsoleUI ui;

    // 점수 관리 객체
    Score score;

    // 게임 현재 상태
    int level;
    int lines;
    int ab_x, ab_y; //화면중 블럭이 나타나는 좌표의 절대위치

    Board board;
    Block current;
    Block next;
    Ranking ranking;

    bool paused;
    bool gameOver;

    // 게임 데이터
    char total_block[21][14]; //화면에 표시되는 블럭들
    struct STAGE stage_data[10];

    // 현재 블록 관련 변수들
    int block_shape, block_angle, block_x, block_y;
    int next_block_shape;
    
    // 로직 함수
    int make_new_block(); //return값으로 block의 모양번호를 알려줌
    int strike_check(int shape, int angle, int x, int y); //블럭이 화면 맨 아래에 부닥쳤는지 검사 부닥치면 1을리턴 아니면 0리턴
    int merge_block(int shape, int angle, int x, int y); //블럭이 바닥에 닿았을때 진행중인 블럭과 쌓아진 블럭을 합침
    void block_start(int shape, int* angle, int* x, int* y); //블럭이 처음 나올때 위치와 모양을 알려줌
    int move_block(int* shape, int* angle, int* x, int* y, int* next_shape); //게임오버는 1을리턴 바닥에 블럭이 닿으면 2를 리턴
    void rotate_block(int shape, int* angle, int* x, int* y);
    void check_full_line();

public:
    GameController();
    
    void run(); // 전체 게임 실행 (로고 출력 - 레벨 선택 - 메인 루프)
    void init(); // 게임 시작 초기화
    void handleInput(); // 메인 루프에서 키 입력 처리 부분 분리
    void resetGame();
    void gameOverProcess(); // 게임오버 후 랭킹 체크
};