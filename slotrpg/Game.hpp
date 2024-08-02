#pragma once
#include <Siv3D.hpp>
#include "Character.hpp"
#include "Enemy.hpp"
#include "Item.hpp"
#include "SlotMachine.hpp"
#include "Opening.hpp"
#include "Event.hpp"

enum class GameState
{
	Opening,
	Field,
	Battle,
	Ending,
	Title,
	GameOver // 新しい状態を追加
};

class Game
{
public:
	Game();
	void update();
	void draw() const;

private:
	void updateOpening();
	void updateField();
	void updateBattle();
	void updateEnding();
	void updateTitle();
	void updateGameOver(); // ゲームオーバーの処理を追加
	void drawBattleUI() const;
	void handlePlayerTurn();
	void handleEnemyTurn();

	Character m_character;
	Array<Enemy> m_enemies;
	Array<Item> m_items;
	Array<Event> m_events;
	GameState m_state;
	Enemy* m_currentEnemy;
	bool m_playerTurn;
	bool m_defending;
	SlotMachine m_slotMachine;
	Opening m_opening;
	int m_defeatedBosses;
	mutable bool m_scrollComplete;
	mutable bool m_showEndingMessage;
	mutable Stopwatch m_endingStopwatch;
	mutable double m_scrollPosition;
	Font m_font;
};
