#include "stdafx.h"
#pragma once


class fileloader { // класс загрузчика файлов
	//конструктор загрузчика - раздает загружаемые файлы переменным
public: fileloader(Texture &t1, Texture &t2, Texture &t3, Texture &t4, Texture &t5, Texture &t6, Texture &t7, SoundBuffer &shotBuffer, SoundBuffer &explBuffer, Music &music);
};