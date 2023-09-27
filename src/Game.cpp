#include "Game.h"
void Game::init()
{
	m_window.create(sf::VideoMode(width, height), "SFML works!");
	m_window.setFramerateLimit(60);
	spawnPlayer();
	sEnemySpawner();
}
void Game::spawnPlayer()
{
	Entity* e = m_eM.addEntity("Player");
	e->cTransform = new CTransform(Vec2(500,500),Vec2(3,3),Vec2(0,0),-5);
	e->cShape = new CShape(50, 6, sf::Color(0,0,255));
	e->cInput = new CInput();
	e->cCollision = new CCollision(e->cShape->circle.getRadius());
	e->cUlt = new CUlt();
	m_player = e;
}
void Game::sEnemySpawner()
{
	float posX = rand()%1024 + 20;
	float posY = rand()%768 + 20;
	float side = rand() % 8 + 1;
	float rgb1 = rand() % 255;
	float rgb2 = rand() % 255;
	float rgb3 = rand() % 255;
	float radius = rand() % 15 + 25;
	Entity* e = m_eM.addEntity("Enemy");
	e->cTransform = new CTransform(Vec2(posX, posY), Vec2(5,5), Vec2(0, 0), -5);
	e->cShape = new CShape(radius, side, sf::Color(rgb1, rgb2, rgb3));
	e->cCollision = new CCollision(e->cShape->circle.getRadius());
}
void Game::run()
{
    while (m_window.isOpen())
    {
		m_eM.update();
		if (!playerAlive)
		{
			spawnPlayer();
			playerAlive = true;
		}
		m_eM.update();
		sCollision();
		sMovement();
		sRender();
		sUserInput();
		if (m_currentFrame - m_lastEnemySpawnTime > 100)
		{
			m_currentFrame = m_lastEnemySpawnTime;
			sEnemySpawner();
		}
		m_currentFrame++;
    }
}
void Game::sRender()
{
	m_window.clear();
	for (auto& e : m_eM.getEntities("Bullet"))
	{

	}
	for (auto &e : m_eM.getEntities())
	{
		if (e->cLifespan != nullptr)
		{
			float opacity = e->cLifespan->remaining * 255 / e->cLifespan->total;
			if (opacity == 0)
			{
				e->destroy();
			}
			else
			{
				sf::Color color = e->cShape->circle.getFillColor();
				sf::Color outlineColor = e->cShape->circle.getOutlineColor();
				color.a = opacity;
				outlineColor.a = opacity;
				e->cShape->circle.setFillColor(color);
				e->cShape->circle.setOutlineColor(outlineColor);
				e->cLifespan->remaining -= 60;
			}
		}
		e->cShape->circle.setPosition(e->cTransform->position);
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);
		m_window.draw(e->cShape->circle);
	}
	
	m_window.display();
}
void Game::sMovement()
{
	m_player->cTransform->speed = { 0,0 };
	if (m_player->cInput->up)
	{
		m_player->cTransform->speed.y = -5;
	}
	if (m_player->cInput->down)
	{
		m_player->cTransform->speed.y = 5;
	}
	if (m_player->cInput->left)
	{
		m_player->cTransform->speed.x = -5;
	}
	if (m_player->cInput->right)
	{
		m_player->cTransform->speed.x = 5;
	}
	for (auto e : m_eM.getEntities())
	{
		e->cTransform->position += e->cTransform->speed;
	}
}
void Game::sCollision()
{
	for (auto e : m_eM.getEntities())
	{
		if (e->cTransform->position.x > width-e->cCollision->radius || e->cTransform->position.x < e->cCollision->radius)
		{
			e->cTransform->speed.x = -e->cTransform->speed.x;
		}
		if (e->cTransform->position.y > height - e->cCollision->radius || e->cTransform->position.y < e->cCollision->radius)
		{
			e->cTransform->speed.y = -e->cTransform->speed.y;
		}


		if (e->cTransform->position.x > width - e->cCollision->radius)
		{
			e->cTransform->position = Vec2(width - e->cCollision->radius, e->cTransform->position.y);
		}
		if (e->cTransform->position.y > height - e->cCollision->radius)
		{
			e->cTransform->position = Vec2(e->cTransform->position.x, height - e->cCollision->radius);
		}
		if (e->cTransform->position.x < e->cCollision->radius)
		{
			e->cTransform->position = Vec2(e->cCollision->radius, e->cTransform->position.y);
		}
		if (e->cTransform->position.y < e->cCollision->radius)
		{
			e->cTransform->position = Vec2(e->cTransform->position.x, e->cCollision->radius);
		}
	}
	for (auto e1 : m_eM.getEntities())
	{
		for (auto e2 : m_eM.getEntities())
		{
			if (e1->getId() != e2->getId() &&
				e1->cTransform->position.getDistance(e2->cTransform->position) < (e1->cCollision->radius + e2->cCollision->radius) * (e1->cCollision->radius + e2->cCollision->radius))
			{
				if (e1->getTag() == "Player" && (e2->getTag() == "Enemy" || e2->getTag() == "SmallEnemy") && e1->isActive() && e2->isActive())
				{
					playerAlive = false;
					e1->destroy();
					e2->destroy();
					if(e2->getTag() == "Enemy")
						split(e2);
				}
				else if ((e2->getTag() == "Bullet" || e2->getTag() == "UltBullet") && (e1->getTag() == "Enemy" || e1->getTag() == "SmallEnemy") && e1->isActive() && e2->isActive())
				{
					e1->destroy();
					if(e2->getTag() != "UltBullet")
						e2->destroy();
					if(e1->getTag() == "Enemy")
						split(e1);
				}
			}
		}
	}


}
void Game::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = true;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = true;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = true;
				break;
			default:
				break;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = false;
				break;
			default:
				break;
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			Vec2 tempVec(event.mouseButton.x, event.mouseButton.y);
			if (event.key.code == sf::Mouse::Left)
			{
				spawnBullet(m_player, tempVec);
			}
			if (event.key.code == sf::Mouse::Right)
			{
				bindUlt(m_player, tempVec);
			}
		}

	}
}
void Game::spawnBullet(Entity* e, Vec2& vec)
{
	Vec2 pos = e->cTransform->position;
	Vec2 speed = calSpeed(e->cTransform->position, vec);
	Entity* bullet = m_eM.addEntity("Bullet");
	bullet->cCollision = new CCollision(10);
	bullet->cShape = new CShape(10,32,sf::Color (0,255,0));
	bullet->cTransform = new CTransform(pos,speed,Vec2(3,3),5);
	bullet->cLifespan = new CLifespan(2400);
}
Vec2 Game::calSpeed(const Vec2& pos, const Vec2& target)const
{
	float angle = atan2(target.y - pos.y, target.x - pos.x);
	
	return Vec2(8 * cos(angle), 8 * sin(angle));
}
void Game::split(Entity* e)
{
	float degree = 360 / e->cShape->point;
	for (int i = 0; i < 360; i += degree)
	{
		Vec2 tempVec(3 * cos(i), 3 * sin(i));
		Entity* smallE = m_eM.addEntity("SmallEnemy");
		smallE->cTransform = new CTransform(e->cTransform->position, tempVec, Vec2(0, 0), -5);
		smallE->cShape = new CShape(e->cShape->circle.getRadius()/2, e->cShape->point, e->cShape->circle.getFillColor());
		smallE->cCollision = new CCollision(smallE->cShape->circle.getRadius());
		smallE->cLifespan = new CLifespan(1200);
	}
}
void Game::bindUlt(Entity* e, Vec2& vec)
{
	float degree = 360 / e->cShape->point;
	for (int i = 0; i < 360; i += degree)
	{
		Vec2 tempVec(3 * cos(i), 3 * sin(i));
		Entity* smallE = m_eM.addEntity("UltBullet");
		smallE->cTransform = new CTransform(e->cTransform->position, tempVec, Vec2(0, 0), -5);
		smallE->cShape = new CShape(e->cShape->circle.getRadius() / 2, e->cShape->point, e->cShape->circle.getFillColor());
		smallE->cCollision = new CCollision(smallE->cShape->circle.getRadius());
		smallE->cLifespan = new CLifespan(12000);
	}
}