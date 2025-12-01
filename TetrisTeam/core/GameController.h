#pragma once
#include <cstdio>
#include <conio.h>
#include <cstring>
#include <windows.h>
#include <ctime>
#include <iostream>
#include <limits>
#include "../ui/Block/Block.h"
#include "../ui/board/Board.h"
#include "../module/Score.h"
#include "../module/Ranking.h"
#include "../ui/ConsoleUI.h"

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
    struct STAGE stage_data[10];

public:
    GameController() = delete;
    ~GameController() = default;
    void run(); // 전체 게임 실행 (로고 출력 - 레벨 선택 - 메인 루프)
    void init(); // 게임 시작 초기화
    void handleInput(); // 메인 루프에서 키 입력 처리 부분 분리
    void resetGame();
    void gameOverProcess(); // 게임오버 후 랭킹 체크
    int moveBlock();
};