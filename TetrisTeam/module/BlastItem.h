#pragma once
#include "Item.h"
class BlastItem : public Item {
public:
    BlastItem();
    virtual bool use(Board& board, Score& score, const Block& block) override;
};
