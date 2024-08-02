#pragma once
#include <Siv3D.hpp>

class Character
{
public:
	Character(const Point& position);
	void move(const Point& delta);
	void draw() const;
	const Point& getPosition() const;
	void takeDamage(int damage);
	void recoverHP(int amount);
	int getHP() const;

private:
	Point m_position;
	int m_hp;
};
