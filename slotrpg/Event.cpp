#include "stdafx.h"
#include "Event.hpp"


Event::Event(const Point& position, const String& message)
	: m_position(position), m_message(message), m_triggered(false), m_font(20)
{
}

void Event::trigger()
{
	m_triggered = true;
}

void Event::draw() const
{
	if (!m_triggered)
	{
		Rect(m_position.x * 40, m_position.y * 40, 40, 40).draw(Palette::Yellow);
	}
	else
	{
		m_font(m_message).drawAt(Scene::Center(), Palette::White);
	}
}

bool Event::isTriggered() const
{
	return m_triggered;
}

const Point& Event::getPosition() const
{
	return m_position;
}
