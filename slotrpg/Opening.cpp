#include <Siv3D.hpp>
#include "Opening.hpp"

Opening::Opening()
	: m_finished(false), m_font(30), m_currentTextIndex(0), m_stopwatch(StartImmediately::Yes) // ここでStartImmediately::Yesを使用
{
	m_texts = {
		U"現代の平凡な学生であるあなたは、",
		U"突如として謎の光に包まれ異世界に転生する。",
		U"目覚めた先は、元素の力が支配する世界。",
		U"あなたは「元素の勇者」として、",
		U"世界を救う使命を負うことになる。"
	};
}

void Opening::update()
{
	if (m_stopwatch.sF() > 3.0) // 3秒ごとに次のテキストを表示
	{
		m_stopwatch.restart();
		m_currentTextIndex++;
		if (m_currentTextIndex >= m_texts.size())
		{
			m_finished = true;
		}
	}
}

void Opening::draw() const
{
	Rect(0, 0, Scene::Width(), Scene::Height()).draw(Palette::Black);
	if (m_currentTextIndex < m_texts.size())
	{
		m_font(m_texts[m_currentTextIndex]).drawAt(Scene::Center(), Palette::White);
	}
}

bool Opening::isFinished() const
{
	return m_finished;
}
