#include "GameController.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

// block 클래스 구현 후 수정예정
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

GameController::GameController() {
    level = 0;
    lines = 0;
    ab_x = 5;
    ab_y = 1;
    paused = false;
    gameOver = false;
}

void GameController::init() {
    srand(static_cast<unsigned>(time(nullptr)));

    // 스테이지 데이터 설정(speed, stick_rate, clear_line)
    stage_data[0] = { 40, 20, 2 };
    stage_data[1] = { 38, 18, 5 };
    stage_data[2] = { 35, 18, 10 };
    stage_data[3] = { 30, 17, 20 };
    stage_data[4] = { 25, 16, 20 };
    stage_data[5] = { 20, 14, 20 };
    stage_data[6] = { 15, 14, 20 };
    stage_data[7] = { 10, 13, 20 };
    stage_data[8] = { 6, 12, 20 };
    stage_data[9] = { 4, 11, 99999 };
}

void GameController::resetGame() {
    // 보드 초기화
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 14; j++) {
            if (j == 0 || j == 13) {
                total_block[i][j] = 1; // 벽
            }
            else {
                total_block[i][j] = 0; // 빈 공간
            }
        }
    }

    for (int j = 0; j < 14; j++) //화면의 제일 밑의 줄은 1로 채운다.
        total_block[20][j] = 1;

    //전역변수 초기화
    lines = 0;
    //score = 0;
    score.resetCombo();// 스코어를 0으로 초기화해주지 않으면 재도전 시 점수가 누적됨
    paused = false;
    gameOver = false;

    //첫 블록 생성
    block_shape = make_new_block();
    next_block_shape = make_new_block();
    block_start(block_shape, &block_angle, &block_x, &block_y);
}

void GameController::run() {
    // 전역 상태 초기화 및 로고 출력
    init();
    ui.showLogo();

    // 한 판 끝날 때마다 다시 시작하는 무한 루프
    while (true) {

        // 키 설명 + 시작 레벨 선택 (기존 input_data)
        level = ui.showLevelMenu();

        resetGame();

        // 초기 블럭, 다음 블럭, 점수판 출력
        ui.show_total_block(total_block, level, ab_x, ab_y);
        ui.show_next_block(next_block_shape, level);
        ui.showGameStat(level, score.getScore(), lines, stage_data[level].clear_line);
        

		// 메인 게임 루프 (기존 main() 안의 for 루프)
		for (int frame = 1; !gameOver; frame++) {
			// 1) 키 입력 처리 (방향키, 회전, 스페이스바)
			handleInput();

			if (!paused) {
				// 블록 자동 하강
				if (frame % stage_data[level].speed == 0) {
					int result = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);
					ui.show_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);

					if (result == 1)
						gameOver = true;

				}


				// 3) 스테이지 클리어 체크
				if (stage_data[level].clear_line <= lines) {
					level++;
					lines = 0;

					ui.showGameStat(level, score.getScore(), lines, stage_data[level].clear_line);        // 점수판 갱신
					ui.show_total_block(total_block, level, ab_x, ab_y);     // 벽 색깔 갱신
					ui.show_next_block(next_block_shape, level); // 오른쪽 박스 테두리 갱신
					ui.show_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);
				}
			}

			// 4) 게임오버 처리
			if (gameOver) {
				gameOverProcess();
				//ui.showGameOver();
				//ui.SetColor(GRAY);
				break;  // 한 판 종료 → while(true) 바깥에서 init() 후 재시작
			}

			// 5) 프레임 간 딜레이
			ui.gotoxy(77, 23);
			if (paused) Sleep(100);
			else Sleep(15);
		}
	}
}

void GameController::gameOverProcess() {
    ui.showGameOver();
    ui.SetColor(GRAY);

    int finalScore = score.getScore();

    if (ranking.isTop10(finalScore)) {
        system("cls");
        ui.gotoxy(10, 5);
        cout << "축하합니다! TOP 10에 성공했습니다!";
        ui.gotoxy(10, 7);
        cout << "이름을 입력하세요: ";

        string name;
        cin >> name;

        ranking.add(name, finalScore);
    }
    system("cls");
    ranking.show();

    ui.gotoxy(10, 20);
    cout << "입력하면 메뉴로 돌아갑니다.";
    _getch();
    system("cls");
}


void GameController::handleInput() {
    if (_kbhit()) {
        char keytemp = _getche();

        // ESC 키로 일시정지
        if (keytemp == 27) {
            paused = !paused;
            if (paused) {
                ui.gotoxy(ab_x + 6, ab_y + 10);
                printf(" PAUSED ");
            }
            else {
                ui.show_total_block(total_block, level, ab_x, ab_y);
                ui.show_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);
            }
            return;
        }

        // 일시정지 중이면 조작 불가
        if (paused) return;

        if (keytemp == EXT_KEY) {
            keytemp = _getche();
            switch (keytemp) {
            case KEY_UP: {
                // 회전하기
                const int new_angle = (block_angle + 1) % 4;
                int dx = 0;

                while (dx >= -4) {
                    if (strike_check(block_shape, new_angle, block_x + dx, block_y) == 0) {
                        ui.erase_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);
                        block_x += dx;
                        rotate_block(block_shape, &block_angle, &block_x, &block_y);
                        ui.show_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);
                        break;
                    }
                    dx--;
                }
                break;
            }
            case KEY_LEFT: {// 왼쪽 이동
                if (block_x > 1) {
                    ui.erase_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);
                    block_x--;
                    if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
                        block_x++;

                    ui.show_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);
                }
                break;
            }

            case KEY_RIGHT: {// 오른쪽 이동
                if (block_x < 14) {
                    ui.erase_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);
                    block_x++;
                    if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
                        block_x--;
                    ui.show_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);
                }
                break;
            }

            case KEY_DOWN: {// 아래로 한 칸 이동
                int result = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);
                ui.show_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);

                if (result == 1) gameOver = true;
                break;
            }
            }
        }


            // 스페이스바
            if (keytemp == 32) {
                while (true) {
                    int result = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);

                    if (result != 0) {
                        if (result == 1) gameOver = true;
                        break;
                    }
                }
                ui.show_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);
            }
        }
    }




int GameController::make_new_block() {
    const int i = rand() % 100;
    if (i <= stage_data[level].stick_rate) //막대기 나올확률 계산
        return 0; //막대기 모양으로 리턴

    return rand() % 6 + 1;
}

int GameController::strike_check(int shape, int angle, int x, int y) {
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

int GameController::merge_block(int shape, int angle, int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (total_block[y + i][x + j] == 1) continue;
            total_block[y + i][x + j] |= block[shape][angle][i][j];
        }
    }
    check_full_line();
    ui.show_total_block(total_block, level, ab_x, ab_y);
    return 0;
}

void GameController::block_start(int shape, int* angle, int* x, int* y) {
    *x = 5;
    *y = -3;
    *angle = 0;
}

int GameController::move_block(int* shape, int* angle, int* x, int* y, int* next_shape) {
    ui.erase_cur_block(*shape, *angle, *x, *y, ab_x, ab_y);
    (*y)++; //블럭을 한칸 아래로 내림

    if (strike_check(*shape, *angle, *x, *y) == 1) {
        (*y)--; // 원위치

        // 게임 오버 판정: 블록이 화면 위쪽(y=0 이상)에서 고정될 때
        if (*y <= 0) {
            return 1; // 게임오버
        }

        merge_block(*shape, *angle, *x, *y);

        // 다음 블록
        *shape = *next_shape;
        *next_shape = make_new_block();
        block_start(*shape, angle, x, y);
        ui.show_next_block(*next_shape, level);

        return 2; // 바닥 닿음
    }
    return 0;
}

void GameController::rotate_block(int shape, int* angle, int* x, int* y) {
    *angle = (*angle + 1) % 4;
}

void GameController::check_full_line() {
    int cleared_lines_count = 0; // 한번에 지워진 라인 수

    for (int i = 0; i < 20; i++) {
        int j;
        for (j = 1; j < 13; j++) {
            if (total_block[i][j] == 0)
                break;
        }
        if (j == 13) //한줄이 다 채워졌음
        {
            lines++;
            cleared_lines_count++;

            // 라인 지우기
            // ui.show_total_block(total_block, level, ab_x, ab_y);
            ui.SetColor(BLUE);
            ui.gotoxy(1 * 2 + ab_x, i + ab_y);
            for (j = 1; j < 13; j++) {
                printf("□");
                Sleep(10);
            }
            ui.gotoxy(1 * 2 + ab_x, i + ab_y);
            for (j = 1; j < 13; j++) {
                printf("  ");
                Sleep(10);
            }

            // 블록 내리기
            for (int k = i; k > 0; k--) {
                for (j = 1; j < 13; j++)
                    total_block[k][j] = total_block[k - 1][j];
            }
            for (j = 1; j < 13; j++)
                total_block[0][j] = 0;

            i--;
        }
    }

    if (cleared_lines_count > 0) {
        score.addLineClear(cleared_lines_count);
        ui.show_total_block(total_block, level, ab_x, ab_y);
    }
      
    else {
        score.resetCombo();
    }

    ui.showGameStat(level, score.getScore(), lines, stage_data[level].clear_line);
}