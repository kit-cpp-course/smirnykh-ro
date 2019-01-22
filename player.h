#include "entity.h"

#pragma once
class player : public Entity  // класс, описывающий игрока
{	
	bool thrust; // переменная, для включения/выключения двигателей
	int playerScore = 0; // счет игрока
	int maxSpeed = 15; // максимальная скорость
public:
	
	player()
	{
		setName("player");
	}
	bool returnThrust() { return thrust; }
	void setThrust(bool set) { thrust = set; }
	int returnPlayerScore() { return playerScore; }
	void setPlayerScore(int newScore) { playerScore = newScore; }
	int returnMaxSpeed() { return maxSpeed; }
	void update();
};