#include "ui/ConsoleUI.h"
#include "core/GameController.h"
#include "core/StructureTypes.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    GameController game;
    game.run();
    return 0;
}



