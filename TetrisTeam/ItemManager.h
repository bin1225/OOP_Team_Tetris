#pragma once
#include <memory>
#include <vector>
#include "Board.h"
#include "Score.h"
#include "Item.h"

class ItemManager {
private:
    std::unique_ptr<Item> currentItem;  // 현재 보유 중인 아이템
    float dropRate;                      // 아이템 생성 확률

    static constexpr float DEFAULT_DROP_RATE = 0.2f;

public:
    ItemManager(float customDropRate = DEFAULT_DROP_RATE);

    void reset();                                    // 아이템 초기화
    void tryGenerate(int linesCleared);              // 아이템 생성 시도
    bool useItem(Board& board, Score& score);        // 아이템 사용
    bool hasItem() const;                            // 아이템 보유 여부

    std::string getCurrentItemName() const;          // 현재 아이템 이름
    std::string getCurrentItemDescription() const;   // 현재 아이템 설명

    void setDropRate(float rate);
    float getDropRate() const;

private:
    std::unique_ptr<Item> createRandomItem();        // 랜덤 아이템 생성
};