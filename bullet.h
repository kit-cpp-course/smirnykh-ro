#include "entity.h"
#pragma once

class bullet : public Entity
{
public:
	bullet()
	{
		setName("bullet");
	}
	void  update();
};
