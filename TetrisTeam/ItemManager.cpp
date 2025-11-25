#include "ItemManager.h"
#include "Item.h"
#include "LineClearItem.h"
#include <cstdlib>
#include <ctime>

ItemManager::ItemManager(float customDropRate)
    : currentItem(nullptr), dropRate(customDropRate) {

    // 랜덤 시드 초기화 (프로그램 시작 시 한 번만)
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }
}

void ItemManager::reset() {
    currentItem.reset();
}

void ItemManager::tryGenerate(int linesCleared) {
    // 이미 아이템을 가지고 있으면 생성하지 않음
    if (currentItem != nullptr) return;

    // 라인을 클리어하지 않았으면 생성 시도 안함
    if (linesCleared <= 0) return;

    // 확률 계산 - 클리어한 라인 수가 많을수록 확률 증가
    float adjustedRate = dropRate * (1.0f + (linesCleared - 1) * 0.1f);

    // 0.0 ~ 1.0 사이의 랜덤 값 생성
    float randomValue = static_cast<float>(rand()) / RAND_MAX;

    if (randomValue < adjustedRate) {
        currentItem = createRandomItem();
    }
}

bool ItemManager::useItem(Board& board, Score& score) {
    if (!currentItem) return false;

    bool success = currentItem->use(board, score);

    if (success) {
        currentItem.reset();  // 사용 후 아이템 제거
    }

    return success;
}

bool ItemManager::hasItem() const {
    return currentItem != nullptr;
}

std::string ItemManager::getCurrentItemName() const {
    return currentItem ? currentItem->getName() : "";
}

std::string ItemManager::getCurrentItemDescription() const {
    return currentItem ? currentItem->getDescription() : "";
}

void ItemManager::setDropRate(float rate) {
    if (rate >= 0.0f && rate <= 1.0f) {
        dropRate = rate;
    }
}

float ItemManager::getDropRate() const {
    return dropRate;
}

std::unique_ptr<Item> ItemManager::createRandomItem() {
    // 현재는 LineClearItem만 존재
    // 추후 다른 아이템 추가 시 랜덤 선택 로직 구현

    // int itemType = rand() % 3;  // 0, 1, 2 중 하나
    // 
    // switch(itemType) {
    //     case 0: return std::make_unique<LineClearItem>();
    //     case 1: return std::make_unique<BombItem>();
    //     case 2: return std::make_unique<SlowDownItem>();
    //     default: return std::make_unique<LineClearItem>();
    // }

    return std::make_unique<LineClearItem>();
}
