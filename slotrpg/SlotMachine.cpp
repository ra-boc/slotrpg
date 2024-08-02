#include "stdafx.h"
#include "SlotMachine.hpp"


SlotMachine::SlotMachine()
{
	m_slots = { SlotSymbol::Fire, SlotSymbol::Water, SlotSymbol::Wind, SlotSymbol::Earth, SlotSymbol::Lightning, SlotSymbol::Ice, SlotSymbol::Light };
	m_textures = {
		Texture(U"fire.png"),
		Texture(U"water.png"),
		Texture(U"wind.png"),
		Texture(U"earth.png"),
		Texture(U"lightning.png"),
		Texture(U"ice.png"),
		Texture(U"light.png")
	};
}

void SlotMachine::draw() const
{
	for (size_t i = 0; i < m_slots.size(); ++i)
	{
		m_textures[static_cast<int>(m_slots[i])].draw(100 + i * 120, 300);
	}
}

void SlotMachine::spin()
{
	for (auto& slot : m_slots)
	{
		slot = static_cast<SlotSymbol>(Random(0, 6));
	}
}

Array<SlotSymbol> SlotMachine::getResults() const
{
	return m_slots;
}
