#include <SFML/Graphics.hpp>
#include "animation.h"
#pragma once

using namespace sf;

class Entity
{
public: // класс сущности
	float x, y, dx, dy, R, angle;
	bool life;
	std::string name;
	Animation anim;

	Entity()
	{
		life = 1; // жизнь сущности (0, если объект уничтожается)
	}

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

	virtual ~Entity() {}; // деструктор
};
