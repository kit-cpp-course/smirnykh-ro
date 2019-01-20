#include "entity.h"
#pragma once

class explosion : public Entity
{
public:
	Texture t3, t7;
	Animation SExpl, SExplS;
	explosion()
	{
		name = "explosion";
		Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5); 
		Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);
		SExpl = sExplosion;
		SExplS = sExplosion_ship;
	}
};
