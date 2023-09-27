#include <SFML/Graphics.hpp>
#include "Vec2.h"
#include <iostream>

class CTransform
{
public:
	Vec2 position = {0,0};
	Vec2 speed = {0.0,0.0};
	Vec2 scale = {0.0,0.0};
	float angle = 0;
	CTransform(Vec2 pos, Vec2 sp, Vec2 scl, float ang)
	{
		position = pos;
		speed = sp;
		scale = scl;
		angle = ang;
	}
};
class CScore
{
public:
	int score = 0;
	CScore(int scr)
	{
		score = scr;
	}
};
class CCollision
{
public:
	float radius = 0;
	float overlapX = 0;
	float overlapY = 0;
	float preOverlapX = 0;
	float preOverlapY = 0;
	CCollision(float rad)
	{
		radius = rad;
	}
};
class CShape
{
public:
	sf::CircleShape circle;
	float point;
	CShape(const float radius, const int points, const sf::Color & color)
	{
		circle = sf::CircleShape(radius-3, points);
		circle.setFillColor(color);
		circle.setOrigin(radius, radius);
		circle.setOutlineThickness(3);
		circle.setOutlineColor(sf::Color::White);
		point = points;
	}
};
class CLifespan
{
public:
	int remaining = 0;
	int total = 0;
	CLifespan(const int total)
	{
		this->total = total;
		this->remaining = total;
	}
};
class CInput
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	CInput(){}
};
class CUlt
{
public:
};

