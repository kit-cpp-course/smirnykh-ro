#include "entity.h"
#pragma once

class bullet : public Entity // класс снарядов
{	
	Texture t5;
	Animation SBull;
public:
	
	bullet()
	{
		setName("bullet");
		t5.loadFromFile("resources/fire_blue.png");
		Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
		SBull = sBullet;
	}
	Animation returnAnim() { return SBull; }
	void  update();
};
