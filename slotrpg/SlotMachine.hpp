#pragma once
#include <Siv3D.hpp>

enum class SlotSymbol
{
	Fire,
	Water,
	Wind,
	Earth,
	Lightning,
	Ice,
	Light
};

class SlotMachine
{
public:
	SlotMachine();
	void draw() const;
	void spin();
	Array<SlotSymbol> getResults() const;

private:
	Array<SlotSymbol> m_slots;
	Array<Texture> m_textures;
};
