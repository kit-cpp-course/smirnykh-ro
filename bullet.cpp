#include "bullet.h"

void bullet::update() { // обновление местоположения снаряда

	bullet::setDX(cos(bullet::returnAngle()*DEGTORAD) * 6);
	bullet::setDY(sin(bullet::returnAngle()*DEGTORAD) * 6);
	float X = bullet::returnX();
	float Y = bullet::returnY();
	X += bullet::returnDX();
	Y += bullet::returnDY();
	bullet::setX(X);
	bullet::setY(Y);

	if (bullet::returnX() > W || bullet::returnX() < 0 || bullet::returnY() > H || bullet::returnY() < 0)
	{  // если снаряд вылетает за пределы экрана - он исчезает
		bullet::setLife(0);
	}
}