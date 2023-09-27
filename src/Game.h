#include <SFML/Graphics.hpp>
#include "EntityManager.h"
class Game
{
	sf::RenderWindow m_window;
	EntityManager m_eM;
	Entity* m_player;
	bool playerAlive = true;
	int width;
	int height;
	int m_score = 0;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;
	bool m_paused = false;
	bool m_running = true;
	void init();
	void spawnPlayer();
	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawner();
	void spawnBullet(Entity* e, Vec2& vec);
	void sCollision();
	Vec2 calSpeed(const Vec2& pos, const Vec2& target)const;
	void split(Entity* e);
	void bindUlt(Entity* e, Vec2& vec);
public:
	void run();
	Game(int width, int height): width(width),height(height)
	{
		init();
	}
	~Game()
	{
		delete m_player;
	}
};

