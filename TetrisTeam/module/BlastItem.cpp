#include "BlastItem.h"
#include <windows.h>

BlastItem::BlastItem() : Item("Blast", "주변폭파") {}

bool BlastItem::use(Board& board, Score& score, const Block& block) {

    int centerX = block.getX() + 1;
    int centerY = block.getY() + 1;
    int radius = 3;

    int removed = board.blastArea(centerX, centerY, radius);

    if (removed > 0) {
        score.addItemBonus(removed * 8);
		itemUI.flashArea(centerX, centerY, radius);
        return true;
    }

    return false;
}
