#pragma once
#include <cstdio>
#include <conio.h>
#include <cstring>
#include <Windows.h>
#include <ctime>
#include <iostream>
#include <limits>
#include "StructureTypes.h"
#include "GameConstants.h"
using namespace std;

class ConsoleUI
{
public:
	int gotoxy(int x, int y);
	void SetColor(int color);
	void showGameOver(); // show_gameover()
	void showLogo(); // show_logo()
	void showLevelMenu(); // input_data()
	int showGameStat(); // show_gamestat()
	void handleInput(int& is_gameover); // 메인 루프에서 키 입력 처리 부분 분리
	int show_next_block(int shape);
	int show_cur_block(int shape, int angle, int x, int y);
	int erase_cur_block(int shape, int angle, int x, int y);
	int show_total_block();
};

