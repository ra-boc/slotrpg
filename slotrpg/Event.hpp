#pragma once
#include <Siv3D.hpp>

class Event
{
public:
	Event(const Point& position, const String& message);
	void trigger();
	void draw() const;
	bool isTriggered() const;
	const Point& getPosition() const;

private:
	Point m_position;
	String m_message;
	bool m_triggered;
	Font m_font;
};
