#include "ItemManager.h"
#include "Item.h"
#include "LineClearItem.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
ItemManager::ItemManager(float customDropRate)
    : currentItem(nullptr), dropRate(customDropRate) {

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
    if (currentItem != nullptr) return;

    //if (linesCleared <= 0) return;

    //float adjustedRate = dropRate + (linesCleared * 0.05f);
    ////if (adjustedRate > 0.50f)
    ////    adjustedRate = 0.50f; // 최대 확률 제한

    //float randomValue = static_cast<float>(rand()) / RAND_MAX;

    //if (randomValue < adjustedRate) {
    //    currentItem = createRandomItem();
    //}
    cout << " 아이템 생성" << endl;
    currentItem = createRandomItem();
}

bool ItemManager::useItem(Board& board, Score& score) {
    if (!currentItem) return false;

    bool success = currentItem->use(board, score);

    if (success) {
        currentItem.reset();
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

     int itemType = rand() % 3;  
     
     switch(itemType) {
         case 0: return std::make_unique<LineClearItem>();
         //case 1: return std::make_unique<BombItem>();
         //case 2: return std::make_unique<SlowDownItem>();
         default: return std::make_unique<LineClearItem>();
     }

    return std::make_unique<LineClearItem>();
}
