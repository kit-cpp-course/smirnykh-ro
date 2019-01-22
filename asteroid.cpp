#include "asteroid.h"

void asteroid::update() { // обновление местоположения астероидов
	float X = asteroid::returnX();
	float Y = asteroid::returnY();
	float DX = asteroid::returnDX();
	float DY = asteroid::returnDY();
	X += DX;
	Y += DY;
	asteroid::setX(X);
	asteroid::setY(Y);

	if (asteroid::returnX() > W) asteroid::setX(0);  if (asteroid::returnX() < 0) asteroid::setX(W);
	if (asteroid::returnY() > H) asteroid::setY(0);  if (asteroid::returnY() < 0) asteroid::setY(H);
}