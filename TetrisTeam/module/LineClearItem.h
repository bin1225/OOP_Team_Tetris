#pragma once
#include "Item.h"

class LineClearItem : public Item {
public:
    LineClearItem();
    virtual bool use(Board& board, Score& score, const Block& block) override;
};