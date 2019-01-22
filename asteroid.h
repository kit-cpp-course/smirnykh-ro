#include "entity.h"

#pragma once
class asteroid : public Entity
{
public:
	asteroid() // конструктор астероида
	{
		setDX(rand() % 8 - 4);
		setDY(rand() % 8 - 4);
		setName("asteroid");
	}
	void  update(); // обновление координат
};