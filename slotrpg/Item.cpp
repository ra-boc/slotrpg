#include "stdafx.h"
#include "Item.hpp"


Item::Item(const Point& position, const String& name)
	: m_position(position), m_name(name), m_collected(false)
{
}

void Item::draw() const
{
	if (!m_collected)
	{
		Rect(m_position.x * 40, m_position.y * 40, 40, 40).draw(Palette::Blue);
	}
}

bool Item::isCollected() const
{
	return m_collected;
}

void Item::collect()
{
	m_collected = true;
}

const Point& Item::getPosition() const
{
	return m_position;
}

const String& Item::getName() const
{
	return m_name;
}
