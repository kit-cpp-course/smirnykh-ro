#include "player.h"


void player::update() { // обновление местоположения корабля
	float newDX = player::returnDX();
	float newDY = player::returnDY();
	if (thrust)
	{
		newDX += cos(player::returnAngle()*DEGTORAD)*0.2;
		newDY += sin(player::returnAngle()*DEGTORAD)*0.2;
		player::setDX(newDX);
		player::setDY(newDY);
	}
	else
	{
		float newDX = player::returnDX();
		newDX *= 0.99;
		player::setDX(newDX);
		float newDY = player::returnDY();
		newDY *= 0.99;
		player::setDX(newDY);
	}

	float speed = sqrt(player::returnDX() * player::returnDX() + player::returnDY() * player::returnDY());
	if (speed > player::maxSpeed)
	{
		float newDX = player::returnDX();
		player::setDX(newDX *= maxSpeed / speed);
		float newDY = player::returnDY();
		player::setDX(newDY *= maxSpeed / speed);
	}
	float newX = player::returnX();
	float newY = player::returnY();
	newX += newDX;
	newY += newDY;

	if (player::returnX() > W) player::setX(0); if (player::returnX() < 0) player::setX(W);
	if (player::returnY() > H) player::setY(0); if (player::returnY() < 0) player::setY(H);
}