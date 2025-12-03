#include "GameController.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "../ui/Block/Block.h"
#include <Windows.h>

using namespace std;

void GameController::init() {
    srand(static_cast<unsigned>(time(nullptr)));

    // 스테이지 데이터 설정(speed, stick_rate, clear_line)
    stage_data[0] = { 40, 20, 5 };
    stage_data[1] = { 38, 18, 7 };
    stage_data[2] = { 35, 18, 10 };
    stage_data[3] = { 30, 17, 20 };
    stage_data[4] = { 25, 16, 25 };
    stage_data[5] = { 20, 14, 30 };
    stage_data[6] = { 15, 14, 35 };
    stage_data[7] = { 10, 13, 40 };
    stage_data[8] = { 6, 12, 50 };
    stage_data[9] = { 4, 11, 99999 };

    ab_x = 5;
    ab_y = 1;
}

void GameController::resetGame() {
    board.reset();

    lines = 0;
    score.resetScore();// 스코어를 0으로 초기화해주지 않으면 재도전 시 점수가 누적됨
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
    ui.setCursorVisible(false);

    while (true) {
        int menuResult = ui.showLevelMenu();

        // 랭킹 조회
        if (menuResult == 99) {
            system("cls");
            ranking.show();

            ui.gotoxy(10, 20);
            cout << "입력하면 메뉴로 돌아갑니다.";

            ui.waitAnyKeyNoEcho();
            
            system("cls");
            continue;
        }

        // 키 설명 + 시작 레벨 선택 (기존 input_data)
        level = menuResult;
        resetGame();

        // 초기 블럭, 다음 블럭, 점수판 출력
        ui.showTotal(board.getGrid(), level, ab_x, ab_y);
        ui.showNext(next, level);
        ui.showGameStat(level, score.getScore(), lines, stage_data[level].clear_line);
        ui.showItemStatus(itemManager.getCurrentItemName(), itemManager.getCurrentItemDescription());
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
                    if (result == 2) {
                        ui.showTotal(board.getGrid(), level, ab_x, ab_y);
                        ui.showNext(next, level);
                        ui.showGameStat(level, score.getScore(), lines, stage_data[level].clear_line);
                    }
				}
				// 3) 스테이지 클리어 체크
				if (stage_data[level].clear_line <= lines) {
					level++;
					lines = 0;

					ui.showGameStat(level, score.getScore(), lines, stage_data[level].clear_line);        // 점수판 갱신
					ui.showTotal(board.getGrid(), level, ab_x, ab_y);     // 벽 색깔 갱신
					ui.showNext(next, level); // 오른쪽 박스 테두리 갱신
					ui.showCurrent(current, ab_x, ab_y);
                    ui.showItemStatus(itemManager.getCurrentItemName(), itemManager.getCurrentItemDescription());
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

        ui.setCursorVisible(true);

        string name;
        cin >> name;

        ui.setCursorVisible(false);

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
        char keytemp = _getch();

        // ESC 키로 일시정지
        if (keytemp == 27) {
            paused = !paused;
            if (paused) {
                ui.SetColor(WHITE);
                ui.gotoxy(ab_x + 9, ab_y + 8);
                printf("┏━━━━━━━━━━━━┓");
                ui.gotoxy(ab_x + 9, ab_y + 9);
                printf("┃   PAUSED   ┃");
                ui.gotoxy(ab_x + 9, ab_y + 10);
                printf("┗━━━━━━━━━━━━┛");
            }
            else {
                ui.clearPauseLogo(ab_x, ab_y);

                ui.showTotal(board.getGrid(), level, ab_x, ab_y);
                ui.showNext(next, level);
                ui.showGameStat(level, score.getScore(), lines, stage_data[level].clear_line);
                ui.showCurrent(current, ab_x, ab_y);
                ui.showItemStatus(itemManager.getCurrentItemName(), itemManager.getCurrentItemDescription());
            }
            return;
        }

        // 일시정지 상태는 입력 차단
        if (paused) return;


        // ★ A 키: 아이템 사용
        if (keytemp == KEY_A_UPPER || keytemp == KEY_A_LOWER) {
            if (itemManager.hasItem()) {

                // 아이템 사용 로직 실행
                bool used = itemManager.useItem(board, score, current);

                if (used) {
                    // 현재 블록 화면에서 지우기
                    ui.eraseCurrent(current, ab_x, ab_y);
                    // 보드, 점수, 아이템 상태창 갱신
                    ui.showTotal(board.getGrid(), level, ab_x, ab_y);
                    ui.showGameStat(level, score.getScore(), lines, stage_data[level].clear_line);
                    ui.showItemStatus(itemManager.getCurrentItemName(), itemManager.getCurrentItemDescription());
                
                    // 현재 블록 폐기 및 다음 블록 소환
                    current = next;
                    next = Block::createBlock();

                    // 새 블록과 next 미리보기 ui 갱신
                    ui.showNext(next, level);
                    ui.showCurrent(current, ab_x, ab_y);
                }
            }
            return;
        }


        // ★ C 키: 테스트용 아이템 생성 (강제 생성)
        if (keytemp == KEY_C_UPPER || keytemp == KEY_C_LOWER) {
            if (!itemManager.hasItem()) {
                itemManager.tryGenerate(1);  // 이 함수 없으면 아래 참고
                ui.showItemStatus(itemManager.getCurrentItemName(), itemManager.getCurrentItemDescription());
            }
            return;
        }

        // 스페이스바: 하드드랍
        if (keytemp == 32) {
            hardDrop();
            return;
        }

        // 확장키 처리
        if (keytemp == EXT_KEY) {
            keytemp = _getch();
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
                if (moveBlock() == 2) {
                    ui.showTotal(board.getGrid(), level, ab_x, ab_y);
                    ui.showNext(next, level);
                    ui.showGameStat(level, score.getScore(), lines, stage_data[level].clear_line);
                    ui.showItemStatus(itemManager.getCurrentItemName(), itemManager.getCurrentItemDescription());
                }
                else {
                    ui.showCurrent(current, ab_x, ab_y);
                }
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
            score.addComboBonus();
            itemManager.tryGenerate(linesCleared);
            ui.showItemStatus(itemManager.getCurrentItemName(), itemManager.getCurrentItemDescription());

        } else {
            score.resetCombo();
        }

        current = next;
        next = Block::createBlock();
        return 2;
    }

    ui.eraseCurrent(current, ab_x, ab_y);
    current = moved;

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
        score.addComboBonus();
        itemManager.tryGenerate(linesCleared);
        ui.showItemStatus(itemManager.getCurrentItemName(), itemManager.getCurrentItemDescription());
    } else {
        score.resetCombo();
    }

    ui.showTotal(board.getGrid(), level, ab_x, ab_y);
    current = next;
    next = Block::createBlock();
    ui.showNext(next, level);
}