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

	// 레벨 출력 및 반환
	int showLevelMenu(); // input_data()

	void showGameStat(int level, int score, int lines, int clear_line); // show_gamestat()
	
	void show_next_block(int shape, int level);
	void show_cur_block(int shape, int angle, int x, int y, int ab_x, int ab_y);
	void erase_cur_block(int shape, int angle, int x, int y, int ab_x, int ab_y);
	void show_total_block(char total_block[21][14], int level, int ab_x, int ab_y);
};

