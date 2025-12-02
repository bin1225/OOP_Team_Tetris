#pragma once
#include <cstdio>
#include <conio.h>
#include <cstring>
#include <windows.h>
#include <ctime>
#include <iostream>
#include <limits>
#include <vector>
#include "../core/StructureTypes.h"
#include "../core/GameConstants.h"
#include "../ui/Block/Block.h"
using std::vector;

class ConsoleUI
{
public:
	int gotoxy(int x, int y);
	void SetColor(int color);
	void showGameOver();
	void showLogo();

	// 레벨 출력 및 반환
	int showLevelMenu();

	void showGameStat(int level, int score, int lines, int clear_line);

    void showNext(const Block& block, int level);
    void showCurrent(const Block& block, int ab_x, int ab_y);
    void eraseCurrent(const Block& block, int ab_x, int ab_y);

	void showTotal(const vector<vector<int>>& grid, int level, int ab_x, int ab_y);
	void showItemStatus(const std::string& itemName, const std::string& itemDesc);
	void showBlastEffect(int centerX, int centerY, int radius);
};

