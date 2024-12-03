#ifndef PCH_H
#define PCH_H

// Standard Header
#include <stdio.h>
#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Windows Header
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")

// Define MACRO

// Free Value Safety
#define SAFE_FREE(p) { if (p != NULL) { free(p); } p = NULL; }

// Keyboard ASCII Define

#define LEFT 75 
#define RIGHT 77 
#define UP  72 
#define DOWN 80 
#define SPACE 32
#define ESC 27
#define ENTER 13

// Console Setting
extern int width; // Console Width
extern int height; // Console Height
extern wchar_t* title; // Console Title

// Console Values
extern FILE* fp; // Reconnected Standard Stream
extern HANDLE consoleInput; // Console Input Handle
extern HANDLE consoleOutput; // Console Output Handle
extern bool isMouseInput; // Check Mouse Input
extern MOUSE_EVENT_RECORD mouseEvent; // Console Mouse Event
extern bool isKeyboardInput; // Check Keyboard Input
extern KEY_EVENT_RECORD keyEvent; // Console Keyboard Event

// Game Setting
extern bool isGameOver; // Flag Value to Check Looping
extern char onKey; // Input Key
extern int x, y; // COORD Values
extern int color, bgColor; // Color Values
extern clock_t before, current; // Get DeltaTime Values
extern const wchar_t *logo;

enum COLORS {	 // Define Colors
	BLACK,		 // 0
	DARK_BLUE,	 // 1
	DARK_GREEN,	 // 2
	DARK_SKYBLUE,// 3
	DARK_RED,	 // 4
	DARK_VIOLET, // 5
	DARK_YELLO,	 // 6
	GRAY,		 // 7
	DARK_GRAY,	 // 8
	BLUE,		 // 9
	GREEN,		 // 10
	SKYBLUE,	 // 11
	RED,		 // 12
	VIOLET,		 // 13
	YELLOW,		 // 14
	WHITE,		 // 15
};

// Default Functions

// Create New Console
void CreateConsole();
// Initalize Console
void Init(int width, int height, const wchar_t* title);
// Release Console
void Release();
// Set Console Size
void SetConsoleSize(int width, int height);
// Position Setting
void SetPosition(int x, int y);
// Color Setting
void SetColor(int newColor, int newBgColor);
// Draw Bitmap into Console
void Draw(const wchar_t* bitmap, int x, int y, int newColor, int newBgColor);
// Check Input Events Every Frames
void CheckInputEvent();
// Get Delta(current_frame - before_frame) Time
float GetDeltaTime();
// Get Mouse Position in Console
COORD GetMousePosition();
// Play Background Sound
void PlaySoundLoop(const wchar_t* path);
// Play Effect Sound
void PlaySoundOnce(const wchar_t* path);
#endif