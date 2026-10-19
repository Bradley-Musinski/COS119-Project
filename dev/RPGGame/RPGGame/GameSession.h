#pragma once

class Player;

class GameSession
{
public:

	GameSession() 
	{}

	void StartSession();
	void SafeZone(Player& player);
	void BattleMode(Player& player);

	void CreateCharacter(Player& player);

	void GameLoop(Player& player);

	bool GetIsNewGame() const { return bIsNewGame; }
	void SetIsNewGame() { bIsNewGame = true; }

	void RequestSessionEnd() { bIsLooping = false; }

	void SaveGame();

private:

	bool bIsNewGame = false;
	bool bIsLooping = true;
};

