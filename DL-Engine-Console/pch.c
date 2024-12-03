#include "pch.h"

// Define Global Values
int width = 80;
int height = 25;
wchar_t* title = L"DL-Engine";

FILE* fp = NULL;
HANDLE consoleInput = NULL;
HANDLE consoleOutput = NULL;
bool isMouseInput = false;
MOUSE_EVENT_RECORD mouseEvent;
bool isKeyboardInput = false;
KEY_EVENT_RECORD keyEvent;

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
    consoleInput = GetStdHandle(STD_INPUT_HANDLE);
    consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Init(int width, int height, const wchar_t* title) {
    SetConsoleSize(width, height);
    SetConsoleTitleW(title);

    // Set Console Input Mode
    DWORD consoleMode;
    GetConsoleMode(consoleInput, &consoleMode);
    consoleMode &= ~ENABLE_QUICK_EDIT_MODE; // Remove Quick Edit Mode
    consoleMode &= ~ENABLE_INSERT_MODE; // Remove Insert Mode
    consoleMode |= ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_EXTENDED_FLAGS; // Add Mouse Input & Keyboard Input Mode
    SetConsoleMode(consoleInput, consoleMode);

    isGameOver = false;
    onKey = 0;
}

void Release() {
    PlaySoundW(NULL, NULL, NULL);
    isGameOver = true;
    consoleInput = NULL;
    consoleOutput = NULL;
}

void SetConsoleSize(int width, int height) {
    // Adjust to within Maxsize
    COORD maxSize = GetLargestConsoleWindowSize(consoleOutput);
    width = (width < maxSize.X) ? width : maxSize.X;
    height = (height < maxSize.Y) ? height : maxSize.Y;

    // Set Buffer Size
    COORD bufferSize;
    bufferSize.X = width;
    bufferSize.Y = height;
    SetConsoleScreenBufferSize(consoleOutput, bufferSize);

    // Set Console Size
    SMALL_RECT consoleSize;
    consoleSize.Left = 0;
    consoleSize.Top = 0;
    consoleSize.Right = width - 1;
    consoleSize.Bottom = height - 1;
    SetConsoleWindowInfo(consoleOutput, true, &consoleSize);
}

void SetPosition(int x, int y) {
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(consoleOutput, position);
}

void SetColor(int newColor, int newBgColor) {
    //Interpolation colors to 4bits(0 to 15 range)
    color = newColor & 0xf;
    bgColor = newBgColor & 0xf;
    SetConsoleTextAttribute(consoleOutput, (bgColor << 4) | color);
}

void Draw(const wchar_t* bitmap, int x, int y, int newColor, int newBgColor) {
    SetPosition(x, y);
    SetColor(newColor, newBgColor);
    wprintf(L"%ls", bitmap);
}

float GetDeltaTime() {
    current = clock();
    float deltaTime = (float)(current - before) / CLOCKS_PER_SEC;
    before = current;
    return deltaTime;
}

void CheckInputEvent() {
    INPUT_RECORD inputRecord;
    DWORD dword;
    ReadConsoleInput(consoleInput, &inputRecord, 1, &dword); // Get Console Input

    isKeyboardInput = false;
    isMouseInput = false;
    if (inputRecord.EventType == KEY_EVENT) { // Keyboard Input
        isKeyboardInput = true;
        keyEvent = inputRecord.Event.KeyEvent;
    }
    else if (inputRecord.EventType == MOUSE_EVENT) { // Mouse Input
        isMouseInput = true;
        mouseEvent = inputRecord.Event.MouseEvent;
    }
}

COORD GetMousePosition() {
    COORD position = { -1,-1, };
    if (isMouseInput) {
        position.X = mouseEvent.dwMousePosition.X;
        position.Y = mouseEvent.dwMousePosition.Y;
    }
    return position;
}

void PlaySoundLoop(const wchar_t *path) {
    PlaySoundW(path, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
}

void PlaySoundOnce(const wchar_t* path) {
    PlaySoundW(path, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}