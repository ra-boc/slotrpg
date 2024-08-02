#include <Siv3D.hpp>
#include "Game.hpp"

void Main()
{
	Game game;

	while (System::Update())
	{
		game.update();
		game.draw();
	}
}
