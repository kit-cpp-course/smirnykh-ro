#include "entity.h"
#pragma once

class bullet : public Entity
{
public:
	Texture t5;
	Animation SBull;
	bullet()
	{
		name = "bullet";
		Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
		SBull = sBullet;
	}
	void  update();
};
