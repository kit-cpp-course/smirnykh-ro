#include "stdafx.h"

TextWork::TextWork() // реализация вывода текста (всего 2 строчки на экран)
{
	font.loadFromFile("resources/pixelfont.ttf");
	gameover.setCharacterSize(16);
	gameover.setFont(font);
	gameover.setStyle(Text::Bold);
	gameover.setString(ssGameover.str());
	gameover.setPosition(W / 2 - 300, H / 2 + 90);
	ssScore << "Score: " << 0;
	text.setCharacterSize(16);
	text.setFont(font);
	text.setStyle(Text::Bold);
	text.setString(ssScore.str());
	text.setPosition(0, 10);
}