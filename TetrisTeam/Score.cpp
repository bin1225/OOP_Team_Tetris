#include "Score.h"

Score::Score() : score(0), combo(0) {
}

// 콤보 초기화
void Score::resetCombo() {
    score = 0;
    combo = 0;
}

// 라인 클리어 점수 추가
void Score::addLineClear(int lines) {
    if (lines < 1 || lines > 4) return;
    
    // 라인 수에 따른 점수 배율 (1줄=1x, 2줄=2.5x, 3줄=5x, 4줄=8x)
    int multiplier = 0;
    switch(lines) {
        case 1: multiplier = 1; break;
        case 2: multiplier = 2; break;
        case 3: multiplier = 5; break;
        case 4: multiplier = 8; break;
    }
    
    int basePoints = BASE_SCORE * multiplier;
    
    score += basePoints;
}


// 콤보 보너스 적용
void Score::addComboBonus() {
    int comboBonus = (combo - 1) * COMBO_BONUS;
	score += comboBonus;
}

int Score::getScore() const {
    return score;
}

int Score::getCombo() const {
    return combo;
}