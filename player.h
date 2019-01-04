#include "entity.h"

#pragma once
class player : public Entity  // класс, описывающий игрока
{
public:
	bool thrust; // переменная, для включения/выключения двигателей
	int playerScore = 0; // счет игрока
	int maxSpeed = 15; // максимальная скорость
	player()
	{
		name = "player";
	}
	void update();
};