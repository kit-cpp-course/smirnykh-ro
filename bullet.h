#include "entity.h"
#pragma once

class bullet : public Entity
{
public:
	bullet()
	{
		name = "bullet";
	}
	void  update();
};
