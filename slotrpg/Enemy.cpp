#include "stdafx.h"
#include "Enemy.hpp"


Enemy::Enemy(const Point& position, const String& name, int hp, int attackPower)
	: m_position(position), m_name(name), m_hp(hp), m_attackPower(attackPower)
{
}

void Enemy::draw() const
{
	Rect(m_position.x * 40, m_position.y * 40, 40, 40).draw(Palette::Green);
}

const Point& Enemy::getPosition() const
{
	return m_position;
}

const String& Enemy::getName() const
{
	return m_name;
}

int Enemy::getHP() const
{
	return m_hp;
}

void Enemy::takeDamage(int damage)
{
	m_hp -= damage;
}

int Enemy::getAttackPower() const
{
	return m_attackPower;
}
