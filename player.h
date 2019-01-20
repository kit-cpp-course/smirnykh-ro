#include "entity.h"

#pragma once
class player : public Entity  // класс, описывающий игрока
{
public:
	bool thrust; // переменная, для включения/выключения двигателей
	int playerScore = 0; // счет игрока
	int maxSpeed = 15; // максимальная скорость
	Texture t1;
	Animation aniStatic;
	Animation aniMove;
	player()
	{
		name = "player";
		t1.loadFromFile("resources/ship.png");
		Animation sPlayer(t1, 0, 0, 37, 36, 1, 0);
		Animation sPlayer_go(t1, 40, 0, 37, 44, 1, 0);
		aniStatic = sPlayer;
		aniMove = sPlayer_go;
	}
	void update();
};