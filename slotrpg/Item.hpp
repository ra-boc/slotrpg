#pragma once
#include <Siv3D.hpp>

class Item
{
public:
	Item(const Point& position, const String& name);
	void draw() const;
	bool isCollected() const;
	void collect();
	const Point& getPosition() const;
	const String& getName() const;

private:
	Point m_position;
	String m_name;
	bool m_collected;
};
