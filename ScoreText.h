#include "stdafx.h"
#pragma once


class TextWork // класс, выводящий текст на экран
{
	Font font; // поле шрифта
	Text text, gameover; // надписи "нажать для игры" и "конец игры"
public:	
	TextWork();
		Font returnFont() { return font; }
		Text returnText() { return text; }
		Text returnGameOver() { return gameover; }
};