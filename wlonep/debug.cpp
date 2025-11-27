#include <iostream>
#include "block/Block.h"
using namespace std;

void printShape(const Block& block) {
    cout << "Block type: " << block.getType()
         << "  Angle: " << block.getAngle()
         << "  Pos(" << block.getX() << "," << block.getY() << ")\n";

    const auto& shape = block.getShape();

    for (int y = 0; y < Block::SIZE; ++y) {
        for (int x = 0; x < Block::SIZE; ++x) {
            cout << (shape[y][x] ? "■ " : ". ");
        }
        cout << '\n';
    }

    cout << endl;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    cout << "=== Block Debug Test ===\n\n";

    // ✅ 1. 기본 생성자 테스트
    const Block b1 = Block::createBlock();
    cout << "[1] 랜덤 생성 블록 (기본 생성자 삭제됨)" << endl;
    printShape(b1);

    // ✅ 2. 특정 타입 생성자 테스트
    Block b2(3, 4, 0); // ㄱ 블록 (예시)
    cout << "[2] 특정 타입 블록 생성 (type=3)" << endl;
    printShape(b2);

    // ✅ 3. 이동 테스트
    cout << "[3] 이동 테스트" << endl;
    b2.moveRight();
    b2.moveDown();
    printShape(b2);

    // ✅ 4. 회전 테스트
    cout << "[4] 회전 테스트 (시계 방향)" << endl;
    b2.rotateRight();
    printShape(b2);

    cout << "[5] 회전 테스트 (반시계 방향)" << endl;
    b2.rotateLeft();
    printShape(b2);

    // ✅ 5. 랜덤 생성 테스트
    cout << "[6] 랜덤 블록 생성" << endl;
    for (int i = 0; i < 3; ++i) {
        Block r = Block::createBlock();
        cout << "랜덤 블록 " << i + 1 << endl;
        printShape(r);
    }

    // ✅ 6. 회전된 블록 복사본 테스트
    cout << "[7] rotated() 테스트 (임시 블록 회전 미리보기)" << endl;
    const Block preview = b2.rotateBlock();
    cout << "원본 블록:" << endl;
    printShape(b2);
    cout << "회전된 복사본:" << endl;
    printShape(preview);

    return 0;
}
