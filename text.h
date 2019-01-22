#include "stdafx.h"
#pragma once



	class TextBox // класс для вывода текста
	{
		Font font;
		Text text, gameover; // переменные для вывода текста
	public: TextBox();
			Font returnFont() { return font; }
			Text returnText() { return text; }
			Text returnGameOver() { return gameover; }
	};