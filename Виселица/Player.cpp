#include "Player.h"

Player::Player()
{
}

void Player::sayThanks()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, phrasePos);
	cout << thanks[(int)rand() % thanksCount];
}

void Player::sayCurse()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, phrasePos);
	cout << curses[(int)rand() % curseCount];
}

void Player::decreaseDeathTime()
{
	deathTime--;
}

int Player::getDeathTime()
{
	return deathTime;
}

void Player::die()
{
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	MoveToEx(hdc, 100, 90, NULL);
	LineTo(hdc, 200, 140);
	MoveToEx(hdc, 200, 90, NULL);
	LineTo(hdc, 100, 140);
	DeleteObject(pen);
}

void Player::drawFloor()
{
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	SelectObject(hdc, pen);
	MoveToEx(hdc, 20, 450, NULL);
	LineTo(hdc, 100, 350);
	LineTo(hdc, 280, 350);
	LineTo(hdc, 200, 450);
	LineTo(hdc, 20,  450);
	DeleteObject(pen);
}

void Player::drawHanging()
{
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	MoveToEx(hdc, 50, 410, NULL);
	LineTo(hdc, 50, 90);
	LineTo(hdc, 150, 90);
	LineTo(hdc, 150, 140);
	DeleteObject(pen);
}

void Player::drawHead()
{
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	Arc(hdc, 110, 140, 170, 200, 0, 0, 0, 0);
	DeleteObject(pen);
}

void Player::drawTile()
{
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	MoveToEx(hdc, 140, 200, NULL);
	LineTo(hdc, 140, 250);
	DeleteObject(pen);
}

void Player::drawLeftHand()
{
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	MoveToEx(hdc, 140, 200, NULL);
	LineTo(hdc, 100, 220);
	DeleteObject(pen);
}
void Player::drawRightHand()
{
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	MoveToEx(hdc, 140, 200, NULL);
	LineTo(hdc, 180, 220);
	DeleteObject(pen);
}

void Player::drawLeftLeng()
{
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	MoveToEx(hdc, 140, 250, NULL);
	LineTo(hdc, 100, 275);
	DeleteObject(pen);
}

void Player::drawRightLeng()
{

	HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	MoveToEx(hdc, 140, 250, NULL);
	LineTo(hdc, 180, 275);
	DeleteObject(pen);
}

void Player::drawPart()
{
	(*this.*part[currentPart])();
	currentPart++;
}

void Player::toZero()
{
	deathTime = 9;
	currentPart = 0;
}

Player::~Player()
{
	ReleaseDC(NULL,hdc);
}
