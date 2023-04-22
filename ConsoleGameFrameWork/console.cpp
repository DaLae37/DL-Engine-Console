#include "console.h"

int main() {
	lines = 10;
	cols = 100;
	Init(lines,cols,"광준이");//매개변수 3개다 3개
	draw();
	PlaySound(TEXT("Sym.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);// 음악
	while (!GameOver) {
		Update();
	}
	Release();
	printf("프로그램 종료\n");
	return 0;
}

void Init(int lines, int cols, const char *title ="title") {
	sprintf(windowCommand, "mode con: lines=%d cols=%d", lines, cols); //콘솔 크기 설정
	system(windowCommand);
	sprintf(windowCommand, "title %s", title); //콘솔창 이름 설정
	system(windowCommand);
	GameOver = false;
	onKey = 0;
}

void draw() {
	setPos(4, 5);
	printf("The music playing now is Clean Bandit - Symphony (cover by J.fla)");
	setPos(4, 6);
	printf("If you want exit, Press P Button to finish this program.");
	setPos(4, 7);
	printf("Please Enjoy Music, Thank you.");
}

void Update() {
	while (kbhit()) {		// kbhit() : 눌른키를 검사하는 함수, 누른 키가 있으면 1반환, 없으면 0 반환
		onKey = _getch();	// 누른키가 있다면 _getch()를 이용해 받은 키의 ASCII 값을 저장
		if (onKey == 'p')	// 지정 키를 누르면 게임오버가 됨
			Release();
	}
}

void Release() {
	PlaySound(NULL, NULL, NULL);
	GameOver = true;
}

void setPos(int x, int y)
{
	COORD POS = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
}

void setColor(int color, int bgcolor)
{
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}