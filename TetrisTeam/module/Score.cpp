#include "Score.h"

Score::Score() : score(0), combo(0) {
}

// �޺� �ʱ�ȭ
void Score::resetCombo() {
    score = 0;
    combo = 0;
}

// ���� Ŭ���� ���� �߰�
void Score::addLineClear(int lines) {
    if (lines < 1 || lines > 4) return;
    
    // ���� ���� ���� ���� ���� (1��=1x, 2��=2.5x, 3��=5x, 4��=8x)
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


// �޺� ���ʽ� ����
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