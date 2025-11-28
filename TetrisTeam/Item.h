#pragma once
#include <string>
#include "Board.h"
#include "Score.h"

class Item {
protected:
    std::string name;
    std::string description;

public:
    Item(const std::string& itemName, const std::string& desc);
    virtual ~Item() = default;

    virtual bool use(Board& board, Score& score) = 0;

    // 아이템 정보 반환
    std::string getName() const;
    std::string getDescription() const;
};