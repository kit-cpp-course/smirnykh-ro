#include "entity.h"

#pragma once
class asteroid : public Entity
{
public:
	asteroid() // ����������� ���������
	{
		dx = rand() % 8 - 4;
		dy = rand() % 8 - 4;
		name = "asteroid";
	}

	void  update(); // ���������� ���������
};