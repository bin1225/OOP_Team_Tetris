#include "GameController.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "../ui/Block/Block.h"

using namespace std;

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

    ab_x = 5;
    ab_y = 1;
}

void GameController::resetGame() {
    board.reset();

    lines = 0;
    score.resetCombo();// 스코어를 0으로 초기화해주지 않으면 재도전 시 점수가 누적됨
    paused = false;
    gameOver = false;

    //첫 블록 생성
    current = Block::createBlock();
    next = Block::createBlock();
}

void GameController::run() {
    // 전역 상태 초기화 및 로고 출력
    init();
    ui.showLogo();

    while (true) {
        // 키 설명 + 시작 레벨 선택 (기존 input_data)
        level = ui.showLevelMenu();
        resetGame();

        // 초기 블럭, 다음 블럭, 점수판 출력
        ui.showTotal(board.getGrid(), level, ab_x, ab_y);
        ui.showNext(next, level);
        ui.showGameStat(level, score.getScore(), lines, stage_data[level].clear_line);

		// 메인 게임 루프 (기존 main() 안의 for 루프)
		for (int frame = 1; !gameOver; frame++) {
			// 1) 키 입력 처리 (방향키, 회전, 스페이스바)
			handleInput();

			if (!paused) {
				// 블록 자동 하강
				if (frame % stage_data[level].speed == 0) {
					int result = moveBlock();
					ui.showCurrent(current, ab_x, ab_y);

					if (result == 1) gameOver = true;
				}
				// 3) 스테이지 클리어 체크
				if (stage_data[level].clear_line <= lines) {
					level++;
					lines = 0;

					ui.showGameStat(level, score.getScore(), lines, stage_data[level].clear_line);        // 점수판 갱신
					ui.showTotal(board.getGrid(), level, ab_x, ab_y);     // 벽 색깔 갱신
					ui.showNext(next, level); // 오른쪽 박스 테두리 갱신
					ui.showCurrent(current, ab_x, ab_y);
				}
			}

			// 4) 게임오버 처리
			if (gameOver) {
				gameOverProcess();
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
                ui.showTotal(board.getGrid(), level, ab_x, ab_y);
                ui.showCurrent(current, ab_x, ab_y);
            }
            return;
        }

        // 일시정지 중이면 조작 불가
        if (paused) return;

        if (keytemp == EXT_KEY) {
            keytemp = _getche();
            switch (keytemp) {
                case KEY_UP:
                    rotateCurrentBlock();
                    return;

                case KEY_LEFT:
                    moveLeft();
                    return;

                case KEY_RIGHT:
                    moveRight();
                    return;

                case KEY_DOWN:
                    moveBlock();
                    ui.showCurrent(current, ab_x, ab_y);
                    return;
            }
        }
    }
}

int GameController::moveBlock() {
    Block moved = current;
    moved.moveDown();
    if (board.checkCollision(moved)) {
        if (current.getY() < 0)
            return 1; // 화면 위에서 충돌

        board.mergeBlock(current);

        int linesCleared = board.clearFullLines();
        if (linesCleared > 0) {
            lines += linesCleared;
            score.addLineClear(linesCleared);
        } else {
            score.resetCombo();
        }

        current = next;
        next = Block::createBlock();
        return 2;
    }

    return 0;
}

void GameController::rotateCurrentBlock() {
    Block rotated = current.rotateBlock();

    ui.eraseCurrent(current, ab_x, ab_y);

    int dx = 0;
    while (dx >= -4) {
        rotated.setPosition(current.getX() + dx, current.getY());

        if (!board.checkCollision(rotated)) {
            current = rotated;
            ui.showCurrent(current, ab_x, ab_y);
            return;
        }
        dx--;
    }

    ui.showCurrent(current, ab_x, ab_y);
}

void GameController::moveLeft() {
    Block moved = current;
    moved.moveLeft();

    if (!board.checkCollision(moved)) {
        ui.eraseCurrent(current, ab_x, ab_y);
        current = moved;
        ui.showCurrent(current, ab_x, ab_y);
    }
}

void GameController::moveRight() {
    Block moved = current;
    moved.moveRight();

    if (!board.checkCollision(moved)) {
        ui.eraseCurrent(current, ab_x, ab_y);
        current = moved;
        ui.showCurrent(current, ab_x, ab_y);
    }
}

void GameController::hardDrop() {
    ui.eraseCurrent(current, ab_x, ab_y);

    while (true) {
        Block dropped = current;
        dropped.moveDown();
        if (board.checkCollision(dropped)) break;

        current = dropped;
    }
    board.mergeBlock(current);
    int linesCleared = board.clearFullLines();

    if (linesCleared > 0) {
        lines += linesCleared;
        score.addLineClear(linesCleared);
    } else {
        score.resetCombo();
    }

    ui.showTotal(board.getGrid(), level, ab_x, ab_y);
    current = next;
    next = Block::createBlock();
    ui.showNext(next, level);
}