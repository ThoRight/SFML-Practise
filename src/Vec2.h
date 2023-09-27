#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>
class Vec2
{
public:
	float x=0;
	float y=0;
	Vec2(float x, float y): x(x), y(y){}
	Vec2(){}
	Vec2 operator +(const Vec2& rhs);
	void operator +=(const Vec2& rhs);
	void operator *=(const Vec2& rhs);
	void operator -=(const Vec2& rhs);
	Vec2& operator =(const Vec2& rhs);
	bool operator ==(const Vec2& rhs)const;
    operator sf::Vector2f() const;
	float getDistance(const Vec2& rhs)const;
	
};

