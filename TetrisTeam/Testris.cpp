#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

//*********************************
// 
//*********************************

#define EXT_KEY			0xffffffe0	//ν 몄媛
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50

//*********************************
//援ъ“泥 
//*********************************
struct STAGE {		//媛 ㅽ댁留ㅼ 대 ㅼ
	int	speed;	//レ媛 �濡 媛 鍮瑜대
	int stick_rate;		//留媛 ㅻ 瑜 0~99 , 99硫 留湲곕 
	int clear_line;
};

enum {
	BLACK,      /*  0 : 源留 */
	DARK_BLUE,    /*  1 : 대  */
	DARK_GREEN,    /*  2 : 대 珥濡 */
	DARK_SKY_BLUE,  /*  3 : 대  */
	DARK_RED,    /*  4 : 대 鍮④ */
	DARK_VOILET,  /*  5 : 대 蹂대 */
	DARK_YELLOW,  /*  6 : 대 몃 */
	GRAY,      /*  7 :  */
	DARK_GRAY,    /*  8 : 대  */
	BLUE,      /*  9 :  */
	GREEN,      /* 10 : 珥濡 */
	SKY_BLUE,    /* 11 :  */
	RED,      /* 12 : 鍮④ */
	VOILET,      /* 13 : 蹂대 */
	YELLOW,      /* 14 : 몃 */
	WHITE,      /* 15 :  */
};

//*********************************
//��
//*********************************
int level;
int ab_x, ab_y;	//硫댁 釉�  醫 �移
int block_shape, block_angle, block_x, block_y;
int next_block_shape;
int score;
int lines;
char total_block[21][14];		//硫댁  釉�
struct STAGE stage_data[10];
char block[7][4][4][4] = {
	//留紐⑥
	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

	//ㅻえ紐⑥
	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

	//'' 紐⑥
	0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

	//''紐⑥
	1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

	//'' 紐⑥
	1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

	//'Z' 紐⑥
	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

	//'S' 紐⑥
	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0

};
//*********************************
//⑥ 
//*********************************
int gotoxy(int x, int y);	//而ㅼ�린湲
void SetColor(int color);	//
int init();					//媛醫蹂 珥湲고
int show_cur_block(int shape, int angle, int x, int y);	//吏以 釉� 硫댁 
int erase_cur_block(int shape, int angle, int x, int y);	//釉 吏  吏곌린  ⑥
int show_total_block();	//ъ몄 釉� 硫댁 .
int show_next_block(int shape);
int make_new_block();	//return媛쇰 block 紐⑥踰몃� �ㅼ
int strike_check(int shape, int angle, int x, int y);	//釉� 硫 留  遺μ낀吏 寃 遺μ硫 1由ы 硫 0由ы
int merge_block(int shape, int angle, int x, int y);	//釉� 諛μ 우 吏以 釉�낵 吏 釉� ⑹묠
int block_start(int shape, int* angle, int* x, int* y);	//釉� 泥 щ 移 紐⑥ �ㅼ
int move_block(int* shape, int* angle, int* x, int* y, int* next_shape);	//寃ㅻ 1由ы 諛μ 釉� 우쇰㈃ 2瑜 由ы
int rotate_block(int shape, int* angle, int* x, int* y);
int show_gameover();
int show_gamestat();
int show_logo();
int input_data();
int check_full_line();


int main()
{
	int i;
	int is_gameover = 0;
	char keytemp;
	init();
	show_logo();
	while (1)
	{

		input_data();
		show_total_block();
		block_shape = make_new_block();
		next_block_shape = make_new_block();
		show_next_block(next_block_shape);
		block_start(block_shape, &block_angle, &block_x, &block_y);
		show_gamestat();
		for (i = 1; 1; i++)
		{
			if (_kbhit())
			{
				keytemp = _getche();
				if (keytemp == EXT_KEY)
				{
					keytemp = _getche();
					switch (keytemp)
					{
					case KEY_UP:		//�湲

						if (strike_check(block_shape, (block_angle + 1) % 4, block_x, block_y) == 0)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							rotate_block(block_shape, &block_angle, &block_x, &block_y);
							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_LEFT:		//쇱そ쇰 대
						if (block_x > 1)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							block_x--;
							if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
								block_x++;

							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_RIGHT:		//ㅻⅨ履쎌쇰 대

						if (block_x < 14)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							block_x++;
							if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
								block_x--;
							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_DOWN:		//濡 대
						is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);
						show_cur_block(block_shape, block_angle, block_x, block_y);
						break;
					}
				}
				if (keytemp == 32)	//ㅽ댁ㅻ瑜 �
				{
					while (is_gameover == 0)
					{
						is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);
					}
					show_cur_block(block_shape, block_angle, block_x, block_y);
				}
			}
			if (i % stage_data[level].speed == 0)
			{
				is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);

				show_cur_block(block_shape, block_angle, block_x, block_y);
			}

			if (stage_data[level].clear_line == lines)	//대━ ㅽ댁
			{
				level++;
				lines = 0;
			}
			if (is_gameover == 1)
			{
				show_gameover();
				SetColor(GRAY);
				break;
			}

			gotoxy(77, 23);
			Sleep(15);
			gotoxy(77, 23);
		}
		init();
	}
	return 0;
}

int gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}

void SetColor(int color)
{
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);
}

int init()
{
	int i, j;

	srand((unsigned)time(NULL));


	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if ((j == 0) || (j == 13))
			{
				total_block[i][j] = 1;
			}
			else {
				total_block[i][j] = 0;
			}
		}
	}

	for (j = 0; j < 14; j++)			//硫댁 � 諛 以 1濡 梨대.
		total_block[20][j] = 1;

	//�� 珥湲고
	level = 0;
	lines = 0;
	ab_x = 5;
	ab_y = 1;

	stage_data[0].speed = 40;
	stage_data[0].stick_rate = 20;
	stage_data[0].clear_line = 20;
	stage_data[1].speed = 38;
	stage_data[1].stick_rate = 18;
	stage_data[1].clear_line = 20;
	stage_data[2].speed = 35;
	stage_data[2].stick_rate = 18;
	stage_data[2].clear_line = 20;
	stage_data[3].speed = 30;
	stage_data[3].stick_rate = 17;
	stage_data[3].clear_line = 20;
	stage_data[4].speed = 25;
	stage_data[4].stick_rate = 16;
	stage_data[4].clear_line = 20;
	stage_data[5].speed = 20;
	stage_data[5].stick_rate = 14;
	stage_data[5].clear_line = 20;
	stage_data[6].speed = 15;
	stage_data[6].stick_rate = 14;
	stage_data[6].clear_line = 20;
	stage_data[7].speed = 10;
	stage_data[7].stick_rate = 13;
	stage_data[7].clear_line = 20;
	stage_data[8].speed = 6;
	stage_data[8].stick_rate = 12;
	stage_data[8].clear_line = 20;
	stage_data[9].speed = 4;
	stage_data[9].stick_rate = 11;
	stage_data[9].clear_line = 99999;
	return 0;
}

int show_cur_block(int shape, int angle, int x, int y)
{
	int i, j;

	switch (shape)
	{
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
		SetColor(VOILET);
		break;
	case 6:
		SetColor(GREEN);
		break;
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((j + y) < 0)
				continue;

			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				printf("");

			}
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}

int erase_cur_block(int shape, int angle, int x, int y)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				printf("  ");
				//break;

			}
		}
	}
	return 0;
}



int show_total_block()
{
	int i, j;
	SetColor(DARK_GRAY);
	for (i = 0; i < 21; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if (j == 0 || j == 13 || i == 20)		//�踰⑥ 곕 몃꼍  蹂
			{
				SetColor((level % 6) + 1);

			}
			else {
				SetColor(DARK_GRAY);
			}
			gotoxy((j * 2) + ab_x, i + ab_y);
			if (total_block[i][j] == 1)
			{
				printf("");
			}
			else {
				printf("  ");
			}

		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}

int make_new_block()
{
	int shape;
	int i;
	i = rand() % 100;
	if (i <= stage_data[level].stick_rate)		//留湲 ы瑜 怨
		return 0;							//留湲 紐⑥쇰 由ы

	shape = (rand() % 6) + 1;		//shape 1~6 媛 ㅼ닿
	show_next_block(shape);
	return shape;
}


int strike_check(int shape, int angle, int x, int y)
{
	int i, j;
	int block_dat;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (((x + j) <= 0) || ((x + j) >= 13))
				block_dat = 1;
			else
				block_dat = total_block[y + i][x + j];

			if ((block_dat == 1) && (block[shape][angle][i][j] == 1))																							//좌측벽의 좌표를 빼기위함
			{
				return 1;
			}
		}
	}
	return 0;
}

int merge_block(int shape, int angle, int x, int y)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (total_block[y + i][x + j] == 1) continue;
			total_block[y + i][x + j] |= block[shape][angle][i][j];
		}
	}
	check_full_line();
	show_total_block();

	return 0;
}

int block_start(int shape, int* angle, int* x, int* y)
{
	*x = 5;
	*y = -3;
	*angle = 0;
	return 0;
}

int show_gameover()
{
	SetColor(RED);
	gotoxy(15, 8);
	printf("");
	gotoxy(15, 9);
	printf("**************************");
	gotoxy(15, 10);
	printf("*        GAME OVER       *");
	gotoxy(15, 11);
	printf("**************************");
	gotoxy(15, 12);
	printf("");
	fflush(stdin);
	Sleep(1000);

	_getche();
	system("cls");

	return 0;
}

int move_block(int* shape, int* angle, int* x, int* y, int* next_shape)
{
	erase_cur_block(*shape, *angle, *x, *y);

	(*y)++;	//釉� 移 濡 대┝
	if (strike_check(*shape, *angle, *x, *y) == 1)
	{
		if (*y < 0)	//寃ㅻ
		{

			return 1;
		}
		(*y)--;
		merge_block(*shape, *angle, *x, *y);
		*shape = *next_shape;
		*next_shape = make_new_block();

		block_start(*shape, angle, x, y);	//angle,x,y ъ명곗
		show_next_block(*next_shape);
		return 2;
	}
	return 0;
}

int rotate_block(int shape, int* angle, int* x, int* y)
{
	*angle = (*angle + 1) % 4;
	return 0;
}

int check_full_line()
{
	int i, j, k;
	for (i = 0; i < 20; i++)
	{
		for (j = 1; j < 13; j++)
		{
			if (total_block[i][j] == 0)
				break;
		}
		if (j == 13)	//以  梨議
		{
			lines++;
			show_total_block();
			SetColor(BLUE);
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++)
			{
				printf("");
				Sleep(10);
			}
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++)
			{
				printf("  ");
				Sleep(10);
			}

			for (k = i; k > 0; k--)
			{
				for (j = 1; j < 13; j++)
					total_block[k][j] = total_block[k - 1][j];
			}
			for (j = 1; j < 13; j++)
				total_block[0][j] = 0;
			score += 100 + (level * 10) + (rand() % 10);
			show_gamestat();
		}
	}
	return 0;
}

int show_next_block(int shape)
{
	int i, j;

	SetColor((level + 1) % 6 + 1);
	for (i = 1; i < 7; i++)
	{
		gotoxy(33, i);
		for (j = 0; j < 6; j++)
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
				printf("");
			else
				printf("  ");
		}
	}

	for (i = 2; i < 6; i++)
	{
		gotoxy(35, i);
		printf("        ");
	}

	show_cur_block(shape, 0, 15, 1);
	return 0;
}



int show_gamestat()
{
	static int printed_text = 0;
	SetColor(GRAY);
	if (printed_text == 0)
	{
		gotoxy(35, 7);
		printf("STAGE");

		gotoxy(35, 9);
		printf("SCORE");

		gotoxy(35, 12);
		printf("LINES");


	}
	gotoxy(41, 7);
	printf("%d", level + 1);
	gotoxy(35, 10);
	printf("%10d", score);
	gotoxy(35, 13);
	printf("%10d", stage_data[level].clear_line - lines);
	return 0;
}

int input_data()
{
	int i = 0;
	SetColor(GRAY);
	gotoxy(10, 7);
	printf("<GAME KEY>");
	Sleep(10);
	gotoxy(10, 8);
	printf(" UP   : Rotate Block        ");
	Sleep(10);
	gotoxy(10, 9);
	printf(" DOWN : Move One-Step Down  ");
	Sleep(10);
	gotoxy(10, 10);
	printf(" SPACE: Move Bottom Down    ");
	Sleep(10);
	gotoxy(10, 11);
	printf(" LEFT : Move Left           ");
	Sleep(10);
	gotoxy(10, 12);
	printf(" RIGHT: Move Right          ");
	Sleep(10);
	gotoxy(10, 13);
	printf("");


	while (i < 1 || i>8)
	{
		gotoxy(10, 3);
		printf("Select Start level[1-8]:       \b\b\b\b\b\b\b");
		scanf_s("%d", &i);
	}


	level = i - 1;
	system("cls");
	return 0;
}

int show_logo()
{
	int i, j;
	gotoxy(13, 3);
	printf("");
	Sleep(100);
	gotoxy(13, 4);
	printf("                ");
	Sleep(100);
	gotoxy(13, 5);
	printf("                                ");
	Sleep(100);
	gotoxy(13, 6);
	printf("                            ");
	Sleep(100);
	gotoxy(13, 7);
	printf("                                ");
	Sleep(100);
	gotoxy(13, 8);
	printf("                        ");
	Sleep(100);
	gotoxy(13, 9);
	printf("");

	gotoxy(28, 20);
	printf("Please Press Any Key~!");

	for (i = 0; i >= 0; i++) {
		if (i % 40 == 0)
		{


			for (j = 0; j < 5; j++)
			{
				gotoxy(18, 14 + j);
				printf("                                                          ");


			}
			show_cur_block(rand() % 7, rand() % 4, 6, 14);
			show_cur_block(rand() % 7, rand() % 4, 12, 14);
			show_cur_block(rand() % 7, rand() % 4, 19, 14);
			show_cur_block(rand() % 7, rand() % 4, 24, 14);
		}
		if (_kbhit())
			break;
		Sleep(30);
	}

	_getche();
	system("cls");

	return 0;
}