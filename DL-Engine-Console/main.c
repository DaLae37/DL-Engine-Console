#include "pch.h"
#include "scene.h"

#define DELAY_CLOSE //If you want close console immediately, remove this line

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    setlocale(LC_ALL, "");
    before = clock();

    // Create Console
    CreateConsole();

    // Setting Console Size
    width = 200;
    height = 50;
    title = L"DL-Engine";

    Init(width, height, title);
    
    CreateScene();
    while (!isGameOver) {
        CheckInputEvent();

        Update(GetDeltaTime());
    }
    
#ifdef DELAY_CLOSE
    char close = _getch();
#endif // DELAY_CLOSE
    FreeConsole();
    return 0;
}