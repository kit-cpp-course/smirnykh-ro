#include "stdafx.h"

using namespace sf;

const int W = 800;
const int H = 600;
std::ostringstream ssGameover;
std::ostringstream ssScore;

void bullet::update() { // обновление местоположения снаряда
	dx = cos(angle*DEGTORAD) * 6;
	dy = sin(angle*DEGTORAD) * 6;
	x += dx;
	y += dy;

	if (x > W || x<0 || y>H || y < 0) {  // если снаряд вылетает за пределы экрана - он исчезает
		life = 0;
	}
}

void player::update() { // обновление местоположения корабля
	if (thrust)
	{
		dx += cos(angle*DEGTORAD)*0.2;
		dy += sin(angle*DEGTORAD)*0.2;
	}
	else
	{
		dx *= 0.99;
		dy *= 0.99;
	}

	float speed = sqrt(dx*dx + dy * dy);
	if (speed > player::maxSpeed)
	{
		dx *= maxSpeed / speed;
		dy *= maxSpeed / speed;
	}

	x += dx;
	y += dy;

	if (x > W) x = 0; if (x < 0) x = W;
	if (y > H) y = 0; if (y < 0) y = H;
}

void asteroid::update() { // обновление местоположения астероидов
	x += dx;
	y += dy;

	if (x > W) x = 0;  if (x < 0) x = W;
	if (y > H) y = 0;  if (y < 0) y = H;
}

Animation::Animation(Texture &t, int x, int y, int w, int h, int count, float Speed) // задание анимации
{
	Frame = 0;
	speed = Speed;

	for (int i = 0; i < count; i++) {
		frames.push_back(IntRect(x + i * w, y, w, h));
	}

	sprite.setTexture(t);
	sprite.setOrigin(w / 2, h / 2);
	sprite.setTextureRect(frames[0]);
}

void Animation::update() // обновление анимации
{
	Frame += speed;
	int n = frames.size();
	if (Frame >= n) Frame -= n;
	if (n > 0) sprite.setTextureRect(frames[int(Frame)]);
}

bool isCollide(Entity *a, Entity *b) // функция столкновения
{
	return (b->x - a->x)*(b->x - a->x) +
		(b->y - a->y)*(b->y - a->y) <
		(a->R + b->R)*(a->R + b->R);
}

int main()
{
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
	
	bool gamestarted = false;

	while (app.isOpen()) // основная логика
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
					b->settings(b->SBull, p->x, p->y, p->angle, 15);
					MyMusic.shotBuffer;
					entities.push_back(b);
				}
		}

		if (Keyboard::isKeyPressed(Keyboard::Space)) // для начала игры необходимо нажать пробел
		{
			gamestarted = true;
		}

		if (gamestarted)
		{
			ssGameover.str("");
			ScoreText.gameover.setString(ssGameover.str()); // для снятия надписи 'game over'

			if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle += 3; // поворот корабля
			if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle -= 3;
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
	
				p->thrust = true;
			}
			else p->thrust = false; // включение двигателя (корабль двигается только вперед)

			for (auto a : entities)
			{
				for (auto b : entities)
				{
					if (a->name == "asteroid" && b->name == "bullet")
					{ // проверка на столкновение астероида со снарядом
						if (isCollide(a, b))
						{
							a->life = false;
							b->life = false;
							p->playerScore += 100;
							ssScore.str("");
							ssScore << "Score: " << p->playerScore;
							ScoreText.text.setString(ssScore.str());
							Entity *e = new explosion();
							e->settings(e->SExpl, a->x, a->y); // создание сущности взрыва
							e->name = "explosion";
							entities.push_back(e);
							MyMusic.explBuffer;

							for (int i = 0; i < 2; i++) // генерация 2-х обломков астероида
							{
								if (a->R == 15) continue;
								Entity *e = new asteroid();
								e->settings(e->aniSRock, a->x, a->y, rand() % 360, 15);
								entities.push_back(e);
							}
						}
					}

					if (a->name == "player" && b->name == "asteroid")
					{ // проверка на столкновение игрока и астероида
						if (isCollide(a, b))
						{
							b->life = false;
							Entity *e = new Entity(); // создание сущности взрыва
							e->settings(e->SExplS, a->x, a->y);
							e->name = "explosion";
							entities.push_back(e);
							ssGameover.str("");
							ssGameover << "Game over. Press 'Space' to play again!";
							ScoreText.gameover.setString(ssGameover.str());
							p->playerScore = 0;
							p->settings(p->aniStatic, W / 2, H / 2, 0, 20);
							p->dx = 0; p->dy = 0;
							MyMusic.explBuffer;
							gamestarted = false;
						}
					}
				}
			}

			if (p->thrust) { 
				p->anim = p->aniMove; // включение ускорения
			}
			else {
				p->anim = p->aniStatic;
			}

			for (auto e : entities) // подготовка к уничтожению сущностей взрывов
			{
				if (e->name == "explosion")
				{
					if (e->anim.isEnd()) e->life = 0;
				}
			}

			if (rand() % 100 == 0) // генерация астероидов
			{
				asteroid *a = new asteroid();
				a->settings(a->aniRock, 0, rand() % H, rand() % 360, 25);
				entities.push_back(a);
			}

			for (auto i = entities.begin(); i != entities.end();)
			{
				Entity *e = *i;

				e->update(); // обновление местоположения и кадра анимации
				e->anim.update();

				if (e->life == false) {   // деструктор сущностей
					i = entities.erase(i); 
					delete e; 
				}
				else i++;
			}
		}

		app.draw(background); // отрисовка
		for (auto i : entities)
			i->draw(app);
		app.draw(ScoreText.gameover);
		app.draw(ScoreText.text);
		app.display();
	}
	return 0;
}
