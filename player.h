#include "entity.h"

#pragma once
class player : public Entity  // �����, ����������� ������
{
public:
	bool thrust; // ����������, ��� ���������/���������� ����������
	int playerScore = 0; // ���� ������
	int maxSpeed = 15; // ������������ ��������
	player()
	{
		name = "player";
	}
	void update();
};