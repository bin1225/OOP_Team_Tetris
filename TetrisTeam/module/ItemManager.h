#pragma once
#include <memory>
#include <vector>
#include "../ui/board/Board.h"
#include "Score.h"
#include "Item.h"

class ItemManager {
private:
    std::unique_ptr<Item> currentItem;  // ���� ���� ���� ������
    float dropRate;                      // ������ ���� Ȯ��

    static constexpr float DEFAULT_DROP_RATE = 0.2f;

public:
    ItemManager(float customDropRate = DEFAULT_DROP_RATE);

    void reset();                                    // ������ �ʱ�ȭ
    void tryGenerate(int linesCleared);              // ������ ���� �õ�
    bool useItem(Board& board, Score& score);        // ������ ���
    bool hasItem() const;                            // ������ ���� ����

    std::string getCurrentItemName() const;          // ���� ������ �̸�
    std::string getCurrentItemDescription() const;   // ���� ������ ����

    void setDropRate(float rate);
    float getDropRate() const;

private:
    std::unique_ptr<Item> createRandomItem();        // ���� ������ ����
};