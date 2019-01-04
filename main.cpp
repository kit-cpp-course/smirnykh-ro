#include "stdafx.h"

using namespace sf;

const int W = 800;
const int H = 600;

float DEGTORAD = 0.017453f;  // константа для перевода в радианы

int Score = 0; // счет игрока

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

	Texture t1, t2, t3, t4, t5, t6, t7; // инициализация текстур

	SoundBuffer shotBuffer, explBuffer;
	Sound Shot(shotBuffer), Explosion(explBuffer); // инициализация звуков

	t1.loadFromFile("resources/ship.png");  // загрузка текстур, звуков и текста
	t2.loadFromFile("resources/background.jpg");
	t3.loadFromFile("resources/type_C.png");
	t4.loadFromFile("resources/rock.png");
	t5.loadFromFile("resources/fire_blue.png");
	t6.loadFromFile("resources/rock_small.png");
	t7.loadFromFile("resources/type_B.png");
	shotBuffer.loadFromFile("resources/shot.wav");
	explBuffer.loadFromFile("resources/explosion.wav");

	Shot.setVolume(50);
	Explosion.setVolume(50);

	Font font;
	font.loadFromFile("resources/pixelfont.ttf");

	Text text, gameover; // переменные для вывода текста
	std::ostringstream ssScore;
	std::ostringstream ssGameover;
	gameover.setCharacterSize(16);
	gameover.setFont(font);
	gameover.setStyle(Text::Bold);
	gameover.setString(ssGameover.str());
	gameover.setPosition(W / 2-300, H/2+90);
	ssScore << "Score: " << Score;
	text.setCharacterSize(16);
	text.setFont(font);
	text.setStyle(Text::Bold);
	text.setString(ssScore.str());
	text.setPosition(0, 10);

	Sprite background(t2);

	Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5); // анимирование спрайтов
	Animation sRock(t4, 0, 0, 64, 64, 16, 0.4);
	Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.8);
	Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
	Animation sPlayer(t1, 0, 0, 37, 36, 1, 0);
	Animation sPlayer_go(t1, 40, 0, 37, 44, 1, 0);
	Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);

	std::list<Entity*> entities;

	player *p = new player(); // генерация и спавн игрока
	p->settings(sPlayer, W / 2, H / 2, 0, 20);
	entities.push_back(p);
	
	bool gamestarted = false;

	while (app.isOpen()) // основная логика
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			if (event.type == Event::KeyPressed) // для того, чтобы игрок не стрелял "спреем"
				if (event.key.code == Keyboard::Space)
				{
					bullet *b = new bullet();
					b->settings(sBullet, p->x, p->y, p->angle, 15);
					Shot.play();
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
			gameover.setString(ssGameover.str()); // для снятия надписи 'game over'

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
							text.setString(ssScore.str());
							Entity *e = new Entity();
							e->settings(sExplosion, a->x, a->y);
							e->name = "explosion";
							entities.push_back(e);
							Explosion.play();

							for (int i = 0; i < 2; i++) // генерация 2-х обломков астероида
							{
								if (a->R == 15) continue;
								Entity *e = new asteroid();
								e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
								entities.push_back(e);
							}
						}
					}

					if (a->name == "player" && b->name == "asteroid")
					{ // проверка на столкновение игрока и астероида
						if (isCollide(a, b))
						{
							b->life = false;
							Entity *e = new Entity();
							e->settings(sExplosion_ship, a->x, a->y);
							e->name = "explosion";
							entities.push_back(e);
							ssGameover.str("");
							ssGameover << "Game over. Press 'Space' to play again!";
							gameover.setString(ssGameover.str());
							p->playerScore = 0;
							p->settings(sPlayer, W / 2, H / 2, 0, 20);
							p->dx = 0; p->dy = 0;
							Explosion.play();
							gamestarted = false;
						}
					}
				}
			}

			if (p->thrust) { 
				p->anim = sPlayer_go;
			}
			else {
				p->anim = sPlayer;
			}

			for (auto e : entities)
			{
				if (e->name == "explosion")
				{
					if (e->anim.isEnd()) e->life = 0;
				}
			}

			if (rand() % 100 == 0) // генерация астероидов
			{
				asteroid *a = new asteroid();
				a->settings(sRock, 0, rand() % H, rand() % 360, 25);
				entities.push_back(a);
			}

			for (auto i = entities.begin(); i != entities.end();) // обработка списка объектов
			{
				Entity *e = *i;

				e->update();
				e->anim.update();

				if (e->life == false) { i = entities.erase(i); delete e; }
				else i++;
			}
		}

		app.draw(background);
		for (auto i : entities)
			i->draw(app);
		app.draw(gameover);
		app.draw(text);
		app.display();
	}
	return 0;
}
