#include "GameController.h"

GameController::GameController() {}

void GameController::run() {
    // 전역 상태 초기화 및 로고 출력
    init();
    ui.showLogo();

    // 한 판 끝날 때마다 다시 시작하는 무한 루프
    while (true) {
        int is_gameover = 0;  // 게임오버 플래그

        // 키 설명 + 시작 레벨 선택 (기존 input_data)
        level = ui.showLevelMenu();

        // 초기 보드 출력
        ui.show_total_block(total_block, level, ab_x, ab_y);

        // 첫 블록, 다음 블록 생성
        block_shape = make_new_block();
        next_block_shape = make_new_block();
        ui.show_next_block(next_block_shape, level);

        // 블록 시작 위치 초기화
        block_start(block_shape, &block_angle, &block_x, &block_y);

        // 점수판 표시
        ui.show_gamestat(level, score, lines, stage_data[level].clear_line);

        // 메인 게임 루프 (기존 main() 안의 for 루프)
        for (int i = 1; ; i++) {
            // 1) 키 입력 처리 (방향키, 회전, 스페이스바)
            handleInput(is_gameover);

            // 2) 자동으로 한 칸씩 내려가는 타이밍
            if (i % stage_data[level].speed == 0) {
                is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);
                ui.show_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);
            }

            // 3) 스테이지 클리어 체크
            if (stage_data[level].clear_line <= lines) {
                level++;
                lines = 0;

                ui.showGameStat(level, score, lines, stage_data[level].clear_line);        // 점수판 갱신
                ui.show_total_block(total_block, level, ab_x, ab_y);     // 벽 색깔 갱신
                ui.show_next_block(next_block_shape, level); // 오른쪽 박스 테두리 갱신
                ui.show_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);
            }

            // 4) 게임오버 처리
            if (is_gameover == 1) {
                ui.showGameOver();
                ui.SetColor(GRAY);
                break;  // 한 판 종료 → while(true) 바깥에서 init() 후 재시작
            }

            // 5) 프레임 간 딜레이
            ui.gotoxy(77, 23);
            Sleep(15);
            //gotoxy(77, 23);
        }

        // 한 판 끝난 후 전체 상태 초기화
        init();
    }
}

void GameController::init() {
    int j;
    srand(static_cast<unsigned>(time(nullptr)));

    // 보드 초기화
    for (int i = 0; i < 20; i++) {
        for (j = 0; j < 14; j++) {
            if (j == 0 || j == 13) {
                total_block[i][j] = 1; // 벽
            }
            else {
                total_block[i][j] = 0; // 빈 공간
            }
        }
    }

    for (j = 0; j < 14; j++) //화면의 제일 밑의 줄은 1로 채운다.
        total_block[20][j] = 1;

    //전역변수 초기화
    level = 0;
    lines = 0;
    ab_x = 5;
    ab_y = 1;
    //score = 0;
    score.resetCombo();// 스코어를 0으로 초기화해주지 않으면 재도전 시 점수가 누적됨

    stage_data[0].speed = 40;
    stage_data[0].stick_rate = 20;
    stage_data[0].clear_line = 2;
    stage_data[1].speed = 38;
    stage_data[1].stick_rate = 18;
    stage_data[1].clear_line = 5;
    stage_data[2].speed = 35;
    stage_data[2].stick_rate = 18;
    stage_data[2].clear_line = 10;
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
}

void GameController::handleInput(int& is_gameover) {
    if (_kbhit()) {
        char keytemp = _getche();

        if (keytemp == EXT_KEY) {
            keytemp = _getche();
            switch (keytemp) {
            case KEY_UP: {
                // 회전하기 (기존 코드 그대로)
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
            case KEY_LEFT: // 왼쪽 이동
                if (block_x > 1) {
                    ui.erase_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);
                    block_x--;
                    if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
                        block_x++;

                    ui.show_cur_block(block_shape, block_angle, block_x, block_y, ab_x, ab_y);
                }
                break;

            case KEY_RIGHT: // 오른쪽 이동
                if (block_x < 14) {
                    erase_cur_block(block_shape, block_angle, block_x, block_y);
                    block_x++;
                    if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
                        block_x--;
                    show_cur_block(block_shape, block_angle, block_x, block_y);
                }
                break;

            case KEY_DOWN: // 아래로 한 칸 이동
                is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);
                show_cur_block(block_shape, block_angle, block_x, block_y);
                break;
            }
        }

        // 스페이스바(하드 드롭)
        if (keytemp == 32) {
            while (is_gameover == 0) {
                is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);
            }
            show_cur_block(block_shape, block_angle, block_x, block_y);
        }
    }
}