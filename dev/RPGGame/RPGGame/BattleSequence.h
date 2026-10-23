#pragma once

class Character;
class Player;
class Enemy;

class BattleSequence
{
public:
	~BattleSequence();

	void Battle(Player& player);
	void BattleMenu(Player& player, const std::vector<Character*>& enemies);

private:
	void CreateEnemies();
	void RollForInitiative(Player& player);
	void RunCombat(Player& player);
	void CharacterStats(Player& player, const std::vector<Character*>& enemies) const;
	void DrawBattleScreen(Player& player, const std::vector<Character*>& enemies, int round) const;
	void DrawStatsAtTop(Player& player, const std::vector<Character*>& enemies) const;
	void Abilities(Player& player, const std::vector<Character*>& enemies);
	bool Bag(Player& player);

	short statsRow = 0; // console row where the stats panel starts

	short GetCursorRow() const;

	// VECTORS
	std::vector<Enemy*> enemyList;
	std::vector<Enemy*> enemyBattleList;
	std::vector<Character*> turnOrder;
	const std::vector<Enemy*>& EnemyList() const { return enemyList; }
	const std::vector<Character*>& TurnOrder() const { return turnOrder; }
	Character* ChooseTarget(const std::vector<Character*>& enemies) const;

	bool bIsLooping = true;
};

