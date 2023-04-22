#include <stdio.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma once
// 키보드 키 ASCII 값 정의
#define LEFT 75 
#define RIGHT 77 
#define UP  72 
#define DOWN 80 
#define SPACE 32
#define ESC 27
#define ENTER 13

#define COMMAND_SIZE 256
using namespace std;

bool GameOver;	// 게임 오버 체크
char onKey;		// 입력한 키를 저장
char windowCommand[COMMAND_SIZE] = { '\0', }; //윈도우 함수 커맨드
int lines; //콘솔창 가로
int cols; // 콘솔창 세로
void Init(int lines, int cols, const char *title); // 초기화
void draw();
void Update();	// 업데이트
void Release();	// 메모리 정리
void setPos(int x, int y);				// 위치 설정
void setColor(int color, int bgcolor);	// 색 설정
time_t start, end;

enum {	// 색깔 정의
	Black,		// 0
	DarkBlue,	// 1
	DarkGreen,	// 2
	DarkSkyBlue,// 3
	DarkRed,	// 4
	DarkViolet,	// 5
	DarkYellow,	// 6
	Gray,		// 7
	DarkGray,	// 8
	Blue,		// 9
	Green,		// 10
	SkyBlue,	// 11
	Red,		// 12
	Violet,		// 13
	Yellow,		// 14
	White		// 15
};