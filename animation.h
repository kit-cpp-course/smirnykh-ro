#include <SFML/Graphics.hpp>
#pragma once

using namespace sf;

class Animation // ����� ������������ ��������
{	float Frame, speed;
	
public:
	Sprite sprite;
	std::vector<IntRect> frames;
	Animation() {}

	Animation(Texture &t, int x, int y, int w, int h, int count, float Speed);

	void update();

	bool isEnd()
	{
		return Frame + speed >= frames.size();
	}
};