#pragma once
#include <Siv3D.hpp>

class Opening
{
public:
	Opening();
	void update();
	void draw() const;
	bool isFinished() const;

private:
	bool m_finished;
	Font m_font;
	Array<String> m_texts;
	int m_currentTextIndex;
	Stopwatch m_stopwatch;
};
