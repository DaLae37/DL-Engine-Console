#pragma once
#include "pch.h"
#include "scene.h"

void CreateScene() {
    PlaySoundLoop(L"Resources/Sounds/bgm.wav");
}

void Update(float deltaTime) {
    Render();
    if (isKeyboardInput) {
        onKey = keyEvent.uChar.AsciiChar;
        if (keyEvent.bKeyDown) {
            SetPosition(150, 10);
            SetColor(WHITE, BLACK);
            printf("input key : %c", onKey);
            if (onKey == 'p') {
                Release();
            }
            else if (onKey == 'k') {
                PlaySoundOnce(L"Resources/Sounds/effect.wav");
            }
        }
    }
    else if (isMouseInput) {
        if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
            COORD mousePosition = GetMousePosition();
            SetPosition(150, 37);
            SetColor(RED, BLUE);
            printf("x : %d y : %d", mousePosition.X, mousePosition.Y);
        }
    }
    SetPosition(150, 20);
    SetColor(BLUE, RED);
    printf("deltaTime : %f", deltaTime);
}

void Render() {
    Draw(logo, 0, 0, WHITE, BLACK);
    Draw(L"마우스와 키보드를 눌러보세요", 100, 10, RED, BLACK);
}