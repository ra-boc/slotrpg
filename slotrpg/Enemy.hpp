#pragma once
#include <Siv3D.hpp>

class Enemy
{
public:
	Enemy(const Point& position, const String& name, int hp, int attackPower);
	void draw() const;
	const Point& getPosition() const;
	const String& getName() const;
	int getHP() const;
	void takeDamage(int damage);
	int getAttackPower() const;

private:
	Point m_position;
	String m_name;
	int m_hp;
	int m_attackPower;
};
