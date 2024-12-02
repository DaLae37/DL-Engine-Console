#pragma once
#include "pch.h"
#include "scene.h"

void CreateScene() {
    PlaySoundLoop(L"Resources/Sounds/bgm.wav");
}

void Update(float deltaTime) {
    onKey = '0';
    Render();
    if (_kbhit()) { // Return 1 if there is a pressed key, return 0 if there is no key
        onKey = _getch(); // Save the ASCII value of the key received using _getch()
        while (_kbhit()) { 
            _getch(); // Remove all remaining datas from input buffer
        }
    }

    if (onKey == 'p') {
        Release();
    }
    else if (onKey == 'k') {
        PlaySoundOnce(L"Resources/Sounds/effect.wav");
    }
}

void Render() {
    Draw(logo, 0, 0, WHITE, BLACK);
}