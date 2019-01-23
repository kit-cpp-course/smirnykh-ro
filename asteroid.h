#include "entity.h"

#pragma once
class asteroid : public Entity // класс астероида, наследующий класс сущности, необходимый для взаимодействия в игре
{
public:
	asteroid() // конструктор астероида - устанавливает унаследованные ускорения и название сущности
	{
		setDX(rand() % 8 - 4); 
		setDY(rand() % 8 - 4);
		setName("asteroid");
	}
	void  update(); // обновление координат
};