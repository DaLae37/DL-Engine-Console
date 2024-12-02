#include "pch.h"

// Define Global Values
int width = 80;
int height = 25;
wchar_t* title = L"DL-Engine";

FILE* fp = NULL;
HANDLE console = NULL;

bool isGameOver = false;
char onKey;
COORD position = { 0,0 };
int color, bgColor;
clock_t before, current;
const wchar_t* logo = L"...............,,,,,,,,,,\n.............,,,,,,,,,,,\n..............,,,,,,,,,,,,\n-::::::::::::::::;;;;;;;;;;;;;~,,,\n:;;;;;;;;!!!!!!!!!!!!!!!!!!!!*;,--\n:;;;;;;;;;;;;!!!!!!!!!!!!!!!!!;---\n:;;;;;;;;;;;!!!!!!!!!!!!!!!!!!;---\n:;;;;;;;;;!!!!!!!!!!!!!!!!!!!*;---\n:;;;;;;;!!!!!!!!!!!!!!!!!!!!**;---\n..:;;;;;;!!!!!!!!!!!!!!!!!!!****;---\n...:!;;;!!!!!!!!!!!!!!!!!!!******;---\n...:!;:::::;;!!!!!!!;!!!*********;---\n...:!!    .,...~!!!*---~*********;---\n...:!!,  .;!!,,,-!!!;-~~*********!---\n...:!!,  .;!!;,,,**!;-~~=********!-~~\n...:!!, ..;!!!,,,-**;~~~=********!~~~\n...;!!- ..;!!!:,,-**;~~~=********!~~~\n...;!!-...;*!!:,--;*;~~~=********!~~~\n...;!!-...;*!!:---;*!~~:=********!~~~\n...;!!-...!*!*:---;*!~~:=********!~~~\n..,;!!-...!***:---**!~::=*******=!~~~\n.,,;!!-...!***----**!~::==*****==!~~~\n,,,;!!-..,!***---!**!:::==****===!~~~\n,,,;*!-..,!**---:=**!:::===*=====!~~~\n,,,;*!-.,,-----;=***!:::;;;!!!!*=!~~:\n,,,;**!;;;;!!******************==!:::\n,,,;*****************============!:::\n,,,;*****************============!:::\n,,,;****************=============!:::\n,,,;***************==============!:::\n,,,;*************================*:::\n,--;************=================*:::\n,--;**********===================*:::\n---:;;;!!!!!!!!!!!!!!!!!!!!!!!***!:::\n-----------~~~~~~~~~~~~:::::::::::::;\n---------~~~~~~~~~~~~~::::::::::::;;;\n--------~~~~~~~~~~~~:::::::::::::;;;`";

void CreateConsole() {
    if (AllocConsole()) {
        // Connect standard outputs, inputs, and error streams to the console
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONIN$", "r", stdin);
        freopen_s(&fp, "CONOUT$", "w", stderr);
    }
    console = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Init(int width, int height, const wchar_t* title) {
    SetConsoleSize(width, height);
    SetConsoleTitleW(title);

    // Hide Cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false; 
    SetConsoleCursorInfo(console, &cursorInfo);

    isGameOver = false;
    onKey = 0;
}

void Release() {
    PlaySoundW(NULL, NULL, NULL);
    isGameOver = true;
    console = NULL;
}

void SetConsoleSize(int width, int height) {
    COORD maxSize = GetLargestConsoleWindowSize(console);
    width = (width < maxSize.X) ? width : maxSize.X;
    height = (height < maxSize.Y) ? width : maxSize.Y;

    COORD bufferSize;
    bufferSize.X = width;
    bufferSize.Y = height;
    SetConsoleScreenBufferSize(console, bufferSize);

    SMALL_RECT windowSize;
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = width - 1;
    windowSize.Bottom = height - 1;
    SetConsoleWindowInfo(console, true, &windowSize);
}

void SetPosition(int x, int y) {
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(console, position);
}

void SetColor(int newColor, int newBgColor) {
    if (newColor != color && newBgColor != bgColor) {
        //Interpolation colors to 4bits(0 to 15 range)
        color &= 0xf;
        bgColor &= 0xf;
        SetConsoleTextAttribute(console, (bgColor << 4) | color);
    }
}

void Draw(wchar_t* bitmap, int x, int y, int newColor, int newBgColor) {
    SetPosition(x, y);
    SetColor(newColor, newBgColor);
    printf("%ls", bitmap);
}

float GetDeltaTime() {
    current = clock();
    float deltaTime = (float)(before - current);
    before = clock();
    return deltaTime;
}

void PlaySoundLoop(const wchar_t *path) {
    PlaySoundW(path, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
}

void PlaySoundOnce(const wchar_t* path) {
    PlaySoundW(path, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}