#pragma once

#include <chrono>

class Score {
private:
    int score;
    int combo;

    // ���� ��� ���
    static const int BASE_SCORE = 100;
    static const int COMBO_BONUS = 50;

public:
    Score();

    void resetCombo();
    void addLineClear(int lines);   // 1~4�� ���� ���� ���
    void addComboBonus();           // �޺� ���ʽ� �߰�
    int getScore() const;
    int getCombo() const;
};