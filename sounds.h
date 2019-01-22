#include "stdafx.h"
#pragma once

class PlayMusicAndSounds // класс для работы со звуком
{
public: 
	SoundBuffer shotBuffer, explBuffer; // одиночные звуки (выстрелы и взрывы)
	Music music; // музыка

	PlayMusicAndSounds()
	{
		Sound Shot(shotBuffer), Explosion(explBuffer);

		Shot.setVolume(50);
		Explosion.setVolume(50);

		shotBuffer.loadFromFile("resources/shot.wav");
		explBuffer.loadFromFile("resources/explosion.wav");

		music.openFromFile("resources/LVCAI - Body.wav");
		music.play();
		music.setLoop(true);
		music.setVolume(100);
	}
};