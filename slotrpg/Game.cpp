#include "Game.hpp"

Game::Game()
	: m_character(Point(1, 1)), m_state(GameState::Opening), m_currentEnemy(nullptr), m_playerTurn(true), m_defending(false), m_slotMachine(), m_defeatedBosses(0), m_scrollComplete(false), m_showEndingMessage(true), m_scrollPosition(Scene::Height()), m_endingStopwatch(StartImmediately::Yes), m_font(30)
{
	m_enemies = {
		Enemy(Point(3, 3), U"Slime", 10, 5),
		Enemy(Point(5, 5), U"Goblin", 20, 7)
	};
	m_items = {
		Item(Point(2, 2), U"Potion"),
		Item(Point(6, 6), U"Elixir")
	};
	m_events = {
		Event(Point(4, 4), U"You found a hidden treasure!"),
		Event(Point(7, 7), U"A wild monster appears!")
	};
}

void Game::update()
{
	if (m_state == GameState::Opening)
	{
		updateOpening();
	}
	else if (m_state == GameState::Field)
	{
		updateField();
	}
	else if (m_state == GameState::Battle)
	{
		if (m_playerTurn)
		{
			handlePlayerTurn();
		}
		else
		{
			handleEnemyTurn();
		}
	}
	else if (m_state == GameState::Ending)
	{
		updateEnding();
		if (m_scrollComplete)
		{
			m_state = GameState::Title;
		}
	}
	else if (m_state == GameState::GameOver) // 新しい状態の処理
	{
		updateGameOver();
		if (m_scrollComplete)
		{
			m_state = GameState::Title;
		}
	}
	else if (m_state == GameState::Title)
	{
		updateTitle();
	}
}

void Game::draw() const
{
	if (m_state == GameState::Opening)
	{
		m_opening.draw();
	}
	else if (m_state == GameState::Field)
	{
		for (const auto& enemy : m_enemies)
		{
			enemy.draw();
		}

		for (const auto& item : m_items)
		{
			item.draw();
		}

		for (const auto& event : m_events)
		{
			event.draw();
		}

		m_character.draw();
	}
	else if (m_state == GameState::Battle)
	{
		drawBattleUI();
	}
	else if (m_state == GameState::Ending || m_state == GameState::GameOver) // 両方のシーンでスタッフロールを描画
	{
		Rect(0, 0, Scene::Width(), Scene::Height()).draw(Palette::Black);

		if (m_showEndingMessage)
		{
			m_font(U"Congratulations! You have defeated all the bosses!").drawAt(Scene::Center(), Palette::White);
		}
		else
		{
			Array<String> credits = {
				U"Elemental Rebirth",
				U"",
				U"Developed by:",
				U"- Developer A",
				U"- Developer B",
				U"- Developer C",
				U"",
				U"Special Thanks:",
				U"- Siv3D Community",
				U"- Family and Friends",
				U"",
				U"Thank you for playing!"
			};

			for (size_t i = 0; i < credits.size(); ++i)
			{
				m_font(credits[i]).drawAt(Scene::Width() / 2, m_scrollPosition + i * 50, Palette::White);
			}
		}
	}
	else if (m_state == GameState::Title)
	{
		Rect(0, 0, Scene::Width(), Scene::Height()).draw(Palette::Black);
		m_font(U"Elemental Rebirth").drawAt(Scene::Center(), Palette::White);
	}
}

void Game::drawBattleUI() const
{
	// 戦闘画面の描画をここに追加
	Rect(0, 0, Scene::Width(), Scene::Height()).draw(Palette::Black);
	m_font(U"Battle!").drawAt(Scene::Center(), Palette::White);

	// 他の戦闘UI要素の描画をここに追加
}

void Game::updateOpening()
{
	m_opening.update();
	if (m_opening.isFinished())
	{
		m_state = GameState::Field;
	}
}

void Game::updateField()
{
	const Point delta[] = {
		Point(1, 0),
		Point(-1, 0),
		Point(0, 1),
		Point(0, -1)
	};

	if (KeyRight.pressed())
	{
		m_character.move(delta[0]);
	}
	if (KeyLeft.pressed())
	{
		m_character.move(delta[1]);
	}
	if (KeyDown.pressed())
	{
		m_character.move(delta[2]);
	}
	if (KeyUp.pressed())
	{
		m_character.move(delta[3]);
	}

	for (auto& item : m_items)
	{
		if (!item.isCollected() && m_character.getPosition() == item.getPosition())
		{
			item.collect();
			Print << U"Collected: " << item.getName();
		}
	}

	for (auto& event : m_events)
	{
		if (!event.isTriggered() && m_character.getPosition() == event.getPosition())
		{
			event.trigger();
		}
	}

	for (auto& enemy : m_enemies)
	{
		if (m_character.getPosition() == enemy.getPosition())
		{
			m_state = GameState::Battle;
			m_currentEnemy = &enemy;
			break;
		}
	}
}

void Game::handlePlayerTurn()
{
	m_slotMachine.draw();

	if (SimpleGUI::Button(U"Spin", Vec2(20, 500)))
	{
		m_slotMachine.spin();
	}

	Array<SlotSymbol> results = m_slotMachine.getResults();

	if (results[0] == results[1] && results[1] == results[2])
	{
		switch (results[0])
		{
		case SlotSymbol::Fire:
			m_currentEnemy->takeDamage(10);
			break;
		case SlotSymbol::Water:
			m_character.recoverHP(10);
			break;
		case SlotSymbol::Wind:
			m_playerTurn = false;
			break;
		case SlotSymbol::Earth:
			m_defending = true;
			break;
		case SlotSymbol::Lightning:
			m_currentEnemy->takeDamage(15);
			break;
		case SlotSymbol::Ice:
			m_currentEnemy->takeDamage(5);
			break;
		case SlotSymbol::Light:
			m_currentEnemy->takeDamage(20);
			break;
		}
	}

	if (m_currentEnemy->getHP() <= 0)
	{
		m_defeatedBosses++;
		if (m_defeatedBosses >= 4)
		{
			m_state = GameState::Ending;
		}
		else
		{
			m_state = GameState::Field;
			m_currentEnemy = nullptr;
		}
	}

	m_playerTurn = false;
}

void Game::handleEnemyTurn()
{
	if (m_currentEnemy != nullptr)
	{
		int damage = m_currentEnemy->getAttackPower();
		if (m_defending)
		{
			damage /= 2;
			m_defending = false;
		}
		m_character.takeDamage(damage);
		Print << U"Enemy attacked! Player HP: " << m_character.getHP();
		if (m_character.getHP() <= 0)
		{
			m_state = GameState::GameOver; // ゲームオーバー状態に遷移
			m_scrollComplete = false;
			m_endingStopwatch.restart();
			m_scrollPosition = Scene::Height();
		}
		m_playerTurn = true;
	}
}

void Game::updateEnding()
{
	if (m_showEndingMessage)
	{
		if (m_endingStopwatch.sF() > 5.0)
		{
			m_showEndingMessage = false;
		}
	}
	else
	{
		m_scrollPosition -= Scene::DeltaTime() * 50;

		if (m_scrollPosition + 350 < 0)
		{
			m_scrollComplete = true;
		}
	}
}

void Game::updateGameOver()
{
	if (m_endingStopwatch.sF() < 5.0)
	{
		m_font(U"Game Over").drawAt(Scene::Center(), Palette::Red);
	}
	else
	{
		m_scrollPosition -= Scene::DeltaTime() * 50;

		Array<String> credits = {
			U"Game Over",
			U"",
			U"Developed by:",
			U"- Developer A",
			U"- Developer B",
			U"- Developer C",
			U"",
			U"Better Luck Next Time!"
		};

		for (size_t i = 0; i < credits.size(); ++i)
		{
			m_font(credits[i]).drawAt(Scene::Width() / 2, m_scrollPosition + i * 50, Palette::White);
		}

		if (m_scrollPosition + credits.size() * 50 < 0)
		{
			m_scrollComplete = true;
		}
	}
}

void Game::updateTitle()
{
	if (SimpleGUI::Button(U"Start", Vec2(Scene::Width() / 2 - 100, Scene::Height() / 2 + 100)))
	{
		m_state = GameState::Opening;
	}
}
