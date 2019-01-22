#include "entity.h"
#pragma once

class explosion : public Entity // класс выводящий на экран эффект взрыва 
{
	Texture t3; // для загрузки текстуры
	Animation SExpl; // для возврата анимации
public:

	explosion()
	{
		t3.loadFromFile("resources/type_C.png");
		setName("explosion");
		Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5); 
		SExpl = sExplosion;
	}
	Animation returnAnim() { return SExpl; } // возвращает анимацию
};
