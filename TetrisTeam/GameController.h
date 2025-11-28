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

    // 게임 데이터
    int level;
    int lines;
    Score score;
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

public:
    GameController();
    
    void run(); // 전체 게임 실행 (로고 출력 - 레벨 선택 - 메인 루프)
    void init(); // 게임 시작 초기화
    void handleInput(int& is_gameover); // 메인 루프에서 키 입력 처리 부분 분리

    // void start(); // 게임 시작 초기화
    void update(); // 매 프레임 갱신
    void draw(); // 화면 출력
    void handleInput(); // 입력 처리
    void gameOverProcess(); // 게임오버 후 랭킹 체크
};