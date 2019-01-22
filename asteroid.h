#include "entity.h"

#pragma once
class asteroid : public Entity
{	
	Texture t4, t6;
	Animation aniRock;
	Animation aniSRock;
public:
	
	asteroid() // конструктор астероида
	{
		setDX(rand() % 8 - 4);
		setDY(rand() % 8 - 4);
		setName("asteroid");
		t4.loadFromFile("resources/rock.png");
		t6.loadFromFile("resources/rock_small.png");
		Animation sRock(t4, 0, 0, 64, 64, 16, 0.4);
		Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.8);
		aniRock = sRock;
		aniSRock = sRock_small;
	}
	Animation returnTextureB() { return aniRock; }
	Animation returnTextureS() { return aniSRock; }

	void  update(); // обновление координат
};