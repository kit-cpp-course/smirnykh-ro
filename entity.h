#include <SFML/Graphics.hpp>
#include "animation.h"
#pragma once

using namespace sf;

class Entity
{	float x, y, dx, dy, R, angle; // основные характеристики сущностей
	bool life; // жизнь сущности
	std::string name; // идентификационное название сущности
public: // класс сущности
	Animation anim;
	Entity() // конструктор сущности (0, если объект уничтожается)
	{
		life = 1;
	}

	float returnX() { return x; } // геттеры и сеттеры инкапсулированных переменных
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

	void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1) // задание настроек сущности (его анимация, местоположение, угол направления движения и размер
	{
		anim = a;
		x = X; y = Y;
		angle = Angle;
		R = radius;
	}

	virtual void update() {}; // виртуальная функция обновления местоположения для сущности

	void draw(RenderWindow &app) { // отрисовка сущности
		anim.sprite.setPosition(x, y);
		anim.sprite.setRotation(angle + 90);
		app.draw(anim.sprite);

		CircleShape circle(R);
		circle.setFillColor(Color(255, 0, 0, 170));
		circle.setPosition(x, y);
		circle.setOrigin(R, R);
	}
	
	virtual ~Entity() {}; // пустой деструктор (удаление происходит в цикле игры)
};
