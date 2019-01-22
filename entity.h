#include <SFML/Graphics.hpp>
#include "stdafx.h"
#pragma once

using namespace sf;

class Entity
{
	float x, y, dx, dy, R, angle;
	bool life;
	std::string name;
	Animation anim;
public: // класс сущности
	Entity()
	{
		life = 1; // жизнь сущности (0, если объект соприкасается с пулей или кораблем)
	}

	float returnX() { return x; }
	void setX(float newX) { x = newX; }
	float returnY() { return y; }
	void setY(float newY) { y = newY; }
	float returnDX() { return dx; }
	void setDX(float newDX) { dx = newDX; }
	float returnDY() { return dy; }
	void setDY(float newDY) { dy = newDY; }
	float returnR() { return R; }
	float returnAngle() { return angle; }
	void setAngle(float newAngle) { angle = newAngle; }
	bool returnLife() { return life; }
	void setLife(bool newLife) { life = newLife; }
	std::string returnName() { return name; }
	void setName(std::string newName) { name = newName; }
	Animation returnAnim() { return anim; }
	void setAnim(Animation NewAnim) { anim = NewAnim; }

	void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1) // задание настроек сущности
	{
		anim = a;
		x = X; y = Y;
		angle = Angle;
		R = radius;
	}

	virtual void update() {};

	void draw(RenderWindow &app) {
		anim.sprite.setPosition(x, y);
		anim.sprite.setRotation(angle + 90);
		app.draw(anim.sprite);

		CircleShape circle(R);
		circle.setFillColor(Color(255, 0, 0, 170));
		circle.setPosition(x, y);
		circle.setOrigin(R, R);
	}

	virtual ~Entity() {}; // пустой деструктор. Удаление объектов происходит в цикле игры
};
