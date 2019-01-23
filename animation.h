#include <SFML/Graphics.hpp>
#pragma once

using namespace sf;

class Animation // класс анимирования объектов
{	float Frame, speed; // frame - кадр, speed - скорость изменения кадра
	
public:
	Sprite sprite; // класс спрайта
	std::vector<IntRect> frames; // переменная разбиения на квадратные кадры
	Animation() {} // стандартный конструктор

	Animation(Texture &t, int x, int y, int w, int h, int count, float Speed); //конструктор анимации разбивает полученное изображение на кадры

	void update(); // изменение анимации

	bool isEnd() // проверяет не закончилась ли анимация
	{
		return Frame + speed >= frames.size();
	}
};