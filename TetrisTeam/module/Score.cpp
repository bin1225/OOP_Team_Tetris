#include "Score.h"

Score::Score() : score(0), combo(0) {
}

void Score::resetScore() {
    score = 0;
    combo = 0;
}

void Score::resetCombo() {
    combo = 0;
}

void Score::addLineClear(int lines) {
    if (lines < 1 || lines > 4) return;
    
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


void Score::addComboBonus() {
    int comboBonus = (combo - 1) * COMBO_BONUS;
	score += comboBonus;
}

void Score::addItemBonus(int points){
	score += points;
}

int Score::getScore() const {
    return score;
}

int Score::getCombo() const {
    return combo;
}