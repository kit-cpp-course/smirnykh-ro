#include "stdafx.h"

using namespace sf;

int::game::run() {

	srand(time(0));
	RenderWindow app(VideoMode(W, H), "Asteroids");
	app.setFramerateLimit(60);
	PlayMusicAndSounds MyMusic;
	TextWork ScoreText;

	Texture t2;
	t2.loadFromFile("resources/background.jpg");
	Sprite background(t2); // установка фона

	std::list<Entity*> entities;

	player *p = new player(); // создание и спавн игрока. При смерти игрок не удаляется, а просто переносится в середину экрана
	p->settings(p->aniStatic, W / 2, H / 2, 0, 20);
	entities.push_back(p);

	while (app.isOpen) // основная логика
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			if (event.type == Event::KeyPressed)
				// для того, чтобы игрок не стрелял "спреем". Так же можно сделать ограничение на количество
				// выпущенных снарядов
				if (event.key.code == Keyboard::Space)
				{
					bullet *b = new bullet();
					b->settings(b->returnAnim(), p->returnX(), p->returnY(), p->returnAngle(), 15);
					MyMusic.shotBuffer;
					entities.push_back(b);
				}
		}

		if (game::returnGetStarted())
		{
			ssGameover.str("");
			ScoreText.returnGameOver().setString(ssGameover.str()); // для снятия надписи 'game over'

			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				float newAngle = p->returnAngle() + 3;
				p->setAngle(newAngle);
			} // поворот корабля
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				float newAngle = p->returnAngle() - 3;
				p->setAngle(newAngle);
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) {

				p->thrust = true;
			}
			else p->thrust = false; // включение двигателя (корабль двигается только вперед)

			for (auto a : entities)
			{
				for (auto b : entities)
				{
					if (a->returnName() == "asteroid" && b->returnName() == "bullet")
					{ // проверка на столкновение астероида со снарядом
						if (isCollide(a, b))
						{
							a->setLife(false);
							b->setLife(false);
							p->playerScore += 100;
							ssScore.str("");
							ssScore << "Score: " << p->playerScore;
							ScoreText.returnText().setString(ssScore.str());
							Entity *e = new explosion();
							e->settings(e->returnAnim, a->returnX(), a->returnY()); // создание сущности взрыва
							e->setName("explosion");
							entities.push_back(e);
							MyMusic.explBuffer;

							for (int i = 0; i < 2; i++) // генерация 2-х обломков астероида
							{
								if (a->returnR() == 15) continue;
								Entity *e = new asteroid();
								e->settings(e->returnAnim, a->returnX(), a->returnY(), rand() % 360, 15);
								entities.push_back(e);
							}
						}
					}

					if (a->returnName() == "player" && b->returnName() == "asteroid")
					{ // проверка на столкновение игрока и астероида
						if (isCollide(a, b))
						{
							b->setLife(false);
							Entity *e = new explosion(); // создание сущности взрыва
							e->settings(e->returnAnim, a->returnX(), a->returnY());
							e->setName("explosion");
							entities.push_back(e);
							ssGameover.str("");
							ssGameover << "Game over. Press 'Space' to play again!";
							ScoreText.returnGameOver().setString(ssGameover.str());
							p->playerScore = 0;
							p->settings(p->aniStatic, W / 2, H / 2, 0, 20);
							p->setDX(0); p->setDY(0);
							MyMusic.explBuffer;
							game::getstarted = false;
						}
					}
				}
			}

			if (p->thrust) {
				p->Entity::setAnim(p->player::aniMove); // отображение включения ускорения
			}
			else {
				p->Entity::setAnim(p->player::aniStatic);
			}

			for (auto e : entities) // подготовка к уничтожению сущностей взрывов
			{
				if (e->returnName() == "explosion")
				{
					if (e->returnAnim().isEnd()) e->setLife(0);
				}
			}

			if (rand() % 100 == 0) // генерация астероидов
			{
				asteroid *a = new asteroid();
				a->settings(a->returnTextureB, 0, rand() % H, rand() % 360, 25);
				entities.push_back(a);
			}

			for (auto i = entities.begin(); i != entities.end();)
			{
				Entity *e = *i;

				e->update(); // обновление местоположения и кадра анимации
				e->returnAnim.update();

				if (e->returnLife() == false) {   // деструктор сущностей
					i = entities.erase(i);
					delete e;
				}
				else i++;
			}
		}

		app.draw(background); // отрисовка
		for (auto i : entities)
			i->draw(app);
		app.draw(ScoreText.returnGameOver());
		app.draw(ScoreText.returnText());
		app.display();
	}
}

bool isCollide(Entity *a, Entity *b) // функция столкновения
{
	return (b->returnX - a->returnX)*(b->returnX - a->returnX) +
		(b->returnY - a->returnY)*(b->returnY - a->returnY) <
		(a->returnR + b->returnR)*(a->returnR + b->returnR);
}