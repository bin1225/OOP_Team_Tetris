#pragma once
#include <string>
#include "../ui/board/Board.h"
#include "../ui/ItemUI.h"
#include "Score.h"

class Item {
protected:
    std::string name;
    std::string description;
	ItemUI itemUI;

public:
    Item(const std::string& itemName, const std::string& desc);
    virtual ~Item() = default;

    virtual bool use(Board& board, Score& score, const Block& block) = 0;

    std::string getName() const;
    std::string getDescription() const;
};