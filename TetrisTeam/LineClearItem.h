#pragma once
#include "Item.h"

class LineClearItem : public Item {
public:
    LineClearItem();
    bool use(Board& board, Score& score) override;
};