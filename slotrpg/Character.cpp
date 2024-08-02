#include "stdafx.h"
#include "Character.hpp"


Character::Character(const Point& position)
	: m_position(position), m_hp(100)
{
}

void Character::move(const Point& delta)
{
	m_position += delta;
}

void Character::draw() const
{
	Rect(m_position.x * 40, m_position.y * 40, 40, 40).draw(Palette::Red);
}

const Point& Character::getPosition() const
{
	return m_position;
}

void Character::takeDamage(int damage)
{
	m_hp -= damage;
}

void Character::recoverHP(int amount)
{
	m_hp += amount;
}

int Character::getHP() const
{
	return m_hp;
}
