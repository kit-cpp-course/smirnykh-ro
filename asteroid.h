#include "entity.h"

#pragma once
class asteroid : public Entity
{ 
public:
	Texture t4, t6;
	Animation aniRock;
	Animation aniSRock;
	asteroid() // конструктор астероида
	{
		dx = rand() % 8 - 4;
		dy = rand() % 8 - 4;
		name = "asteroid";
		t4.loadFromFile("resources/rock.png");
		t6.loadFromFile("resources/rock_small.png");
		Animation sRock(t4, 0, 0, 64, 64, 16, 0.4);
		Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.8);
	}

	void  update(); // обновление координат
};