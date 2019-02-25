#pragma once
#include "main.h"
class Player
{
public:
	Player();//конструктор по умолчанию
	void sayThanks();//слова благодарности
	void sayCurse();//прокл€тие
	void decreaseDeathTime();//уменьшить врем€ до смерти
	int getDeathTime();//получить врем€ до смерти
	void die();//анимаци€ проигрыша
	void drawPart();//нарисовать следующую часть
	void toZero();//обнул€ет все
	~Player();//деструктор
private:
	HDC hdc = GetDC(GetConsoleWindow());
	void drawFloor();
	void drawHanging();
	void drawHead();
	void drawTile();
	void drawLeftHand();
	void drawRightHand();
	void drawLeftLeng();
	void drawRightLeng();
	COORD phrasePos = { 0,1 };//позици€ фраз
	static const int curseCount = 1;//количество угроз
	static const int thanksCount = 3;//количество благодраностей
	string curses[curseCount] = {"„ума ты болотна€!!"};
	string thanks[thanksCount] = { "—пасибо деду за победу", "„ел, благодарствую","—пасибо камрад" };
	int deathTime = 9, currentPart = 0;//врем€ до смерти
	void (Player::*part[9])() = {&Player::drawFloor, &Player::drawHanging, &Player::drawHead, &Player::drawTile, &Player::drawLeftHand, &Player::drawRightHand, &Player::drawLeftLeng, &Player::drawRightLeng, &Player::die };
};

