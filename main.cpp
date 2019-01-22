#include "stdafx.h"

using namespace sf;
using namespace std;

bool isCollide(Entity *a, Entity *b);

game::game()
{
	bool gamestarted = false;
	srand(time(0));
	RenderWindow app(VideoMode(W, H), "Asteroids");
	app.setFramerateLimit(60);

	Texture t1, t2, t3, t4, t5, t6, t7; // инициализация текстур
	t1.loadFromFile("resources/ship.png");  // загрузка текстур, звуков и текста
	t2.loadFromFile("resources/background.jpg");
	t3.loadFromFile("resources/type_C.png");
	t4.loadFromFile("resources/rock.png");
	t5.loadFromFile("resources/fire_blue.png");
	t6.loadFromFile("resources/rock_small.png");
	t7.loadFromFile("resources/type_B.png");

	SoundBuffer shotBuffer, explBuffer;
	Sound Shot(shotBuffer), Explosion(explBuffer); // инициализация звуков
	shotBuffer.loadFromFile("resources/shot.wav");
	explBuffer.loadFromFile("resources/explosion.wav");

	TextBox TBOX;
	Text GameOver = TBOX.returnGameOver();
	Text text = TBOX.returnText();

	Music music;
	music.openFromFile("resources/dB soundworks - Betus Blues.wav");
	music.play();
	music.setLoop(true);
	music.setVolume(20);

	Shot.setVolume(50);
	Explosion.setVolume(50);

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
					float X = p->returnX();
					float Y = p->returnY();
					float Angle = p->returnAngle();

					b->settings(sBullet, X, Y, Angle, 15);
					Shot.play();
					entities.push_back(b);
				}
		}

		if (Keyboard::isKeyPressed(Keyboard::Space)) // для начала игры необходимо нажать пробел
			gamestarted = true;

		if (Keyboard::isKeyPressed(Keyboard::Escape)) // закрытие игры при нажатии escape
			break;

		if (gamestarted)
		{
			ssGameover.str("");
			GameOver.setString(ssGameover.str()); // для снятия надписи 'game over'

			if (Keyboard::isKeyPressed(Keyboard::Right)) p->setAngle(p->returnAngle() + 3); // поворот корабля
			if (Keyboard::isKeyPressed(Keyboard::Left))  p->setAngle(p->returnAngle() - 3);
			if (Keyboard::isKeyPressed(Keyboard::Up)) {

				p->setThrust(true);
			}
			else p->setThrust(false); // включение двигателя (корабль двигается только вперед)

			for (auto a : entities)
			{
				for (auto b : entities)
				{
					string aName = a->returnName();
					string bName = b->returnName();
					if (aName == "asteroid" && bName == "bullet")
					{ // проверка на столкновение астероида со снарядом
						if (isCollide(a, b))
						{
							a->setLife(false);
							b->setLife(false);
							int oldScore = p->returnPlayerScore();
							p->setPlayerScore(oldScore + 100);
							ssScore.str("");
							ssScore << "Score: " << p->returnPlayerScore();
							text.setString(ssScore.str());
							Entity *e = new Entity();
							float AX = a->returnX();
							float AY = a->returnY();
							e->settings(sExplosion, AX, AY);
							e->setName("explosion");
							entities.push_back(e);
							Explosion.play();

							for (int i = 0; i < 2; i++) // создание 2-х обломков астероида
							{
								if (a->returnR() == 15) continue;
								Entity *e = new asteroid();
								e->settings(sRock_small, a->returnX(), a->returnY(), rand() % 360, 15);
								entities.push_back(e);
							}
						}
					}

					if (a->returnName() == "player" && b->returnName() == "asteroid")
					{ // проверка на столкновение игрока и астероида
						if (isCollide(a, b))
						{
							b->setLife(false);
							Entity *e = new Entity();
							e->settings(sExplosion_ship, a->returnX(), a->returnX());
							e->setName("explosion");
							entities.push_back(e);
							ssGameover.str("");
							ssGameover << "Game over. Press 'Space' to play again!";
							GameOver.setString(ssGameover.str());
							p->setPlayerScore(0);
							p->settings(sPlayer, W / 2, H / 2, 0, 20);
							p->setDX(0); p->setDY(0);
							Explosion.play();
							gamestarted = false;
						}
					}
				}
			}

			if (p->returnThrust()) { // изменение спрайта при движении
				p->setAnim(sPlayer_go);
			}
			else {
				p->setAnim(sPlayer);
			}

			for (auto e : entities) // снятие с экрана взрывов
			{
				if (e->returnName() == "explosion")
				{
					auto Check = e->returnAnim();
					if (Check.isEnd()) e->setLife(0);
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

				if (e->returnLife() == false) { i = entities.erase(i); delete e; } // удаление уничтоженных сущностей (взрывы и астероиды)
				else i++;
			}
		}

		// отрисовка
		app.draw(background);
		for (auto i : entities)
			i->draw(app);
		app.draw(GameOver);
		app.draw(text);
		app.display();
	}
}

TextBox::TextBox() // конструктор текста
{
	font.loadFromFile("resources/pixelfont.ttf");
	gameover.setCharacterSize(16);
	gameover.setFont(font);
	gameover.setStyle(Text::Bold);
	gameover.setString(ssGameover.str());
	gameover.setPosition(W / 2 - 300, H / 2 + 90);
	ssScore << "Score: " << Score;
	text.setCharacterSize(16);
	text.setFont(font);
	text.setStyle(Text::Bold);
	text.setString(ssScore.str());
	text.setPosition(0, 10);
}

void bullet::update() { // обновление местоположения снаряда
	setDX(cos(returnAngle()*DEGTORAD) * 6);
	setDY(sin(returnAngle()*DEGTORAD) * 6);
	setX(returnX() + returnDX());
	setY(returnY() + returnDY());

	if (returnX() > W || returnX()<0 || returnY()>H || returnY() < 0) {  // если снаряд вылетает за пределы экрана - он исчезает
		setLife(false);
	}
}

void player::update() { // обновление местоположения корабля
	if (thrust)
	{
		float DX = player::returnDX();
		float DY = player::returnDY();
		float Angle = player::returnAngle();
		player::setDX(DX + cos(Angle*DEGTORAD)*0.2);
		player::setDY(DY + sin(Angle*DEGTORAD)*0.2);
	}
	else
	{
		setDX(returnDX()*0.99);
		setDY(returnDY()*0.99);
	}

	float speed = sqrt(returnDX() * returnDX() + returnDY() * returnDY());
	if (speed > player::maxSpeed)
	{
		setDX(returnDX() * maxSpeed / speed);
		setDY(returnDY() * maxSpeed / speed);
	}

	setX(returnX() + returnDX());
	setY(returnY() + returnDY());

	if (returnX() > W) setX(0); if (returnX() < 0) setX(W);
	if (returnY() > H) setY(0); if (returnY() < 0) setY(H);
}

void asteroid::update() { // обновление местоположения астероидов
	Entity::setX(returnX()+returnDX());
	Entity::setY(returnY() + returnDY());

	if (returnX() > W) setX(0);  if (returnX() < 0) setX(W);
	if (returnY() > H) setY(0);  if (returnY() < 0) setY(H);
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
	return (b->returnX() - a->returnX())*(b->returnX() - a->returnX()) +
		(b->returnY() - a->returnY())*(b->returnY()- a->returnY()) <
		(a->returnR() + b->returnR())*(a->returnR() + b->returnR());
}

int main()
{
	game game;
	return 0;
}
