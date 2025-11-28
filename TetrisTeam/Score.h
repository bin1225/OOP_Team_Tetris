#pragma once

#include <chrono>

class Score {
private:
    int score;
    int combo;

    // 점수 계산 상수
    static const int BASE_SCORE = 100;
    static const int COMBO_BONUS = 50;

public:
    Score();

    void resetCombo();
    void addLineClear(int lines);   // 1~4줄 제거 점수 계산
    void addComboBonus();           // 콤보 보너스 추가
    int getScore() const;
    int getCombo() const;
};