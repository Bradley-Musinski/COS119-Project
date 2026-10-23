#include <thread>
#include "GameEngine.h"
#include "GameSession.h"
#include "SaveSystem.h"
#include "Input.h"
#include "CharacterCreator.h"
#include "BattleSequence.h"
#include "Town.h"
#include "Player.h"
#include "Goblin.h"
#include "Skeleton.h"
#include "Dialogue.h"

void GameSession::StartSession()
{
	bIsLooping = true;

	Player* player = new Player();

	if (bIsNewGame)
	{
		bIsNewGame = false;
		GEngine->ClearConsole();

		CreateCharacter(*player);
	}
	else
	{
		SaveSystem::LoadPlayer(*player, saveFile);
		GEngine->Print("Player Data Loaded!", Color::Red, 1);
		std::this_thread::sleep_for(2s);
	}

	GameLoop(*player);
}

void GameSession::CreateCharacter(Player& player)
{

	GEngine->RegisterActor(&player); // Registers the actor to the vector so it will be added to the destruction list

	// Calls the CreateCharacter method from the CharacterCreator namespace
	CharacterCreator::CreateCharacter(player);
}

void GameSession::SafeZone(Player& player) // This will go in its own class eventually
{
	Town town(*this, player);
	town.TownArea();

}

void GameSession::BattleMode(Player& player)
{
	BattleSequence battle;
	battle.Battle(player);

}


void GameSession::GameLoop(Player& player)
{
	while (bIsLooping)
	{
		SafeZone(player);

		if (bIsLooping)
		{
			BattleMode(player);
			GEngine->ProcessDeferredDestruction();
		}

		GEngine->ProcessDeferredDestruction();
		SaveSystem::SaveGame(player);
	}
}

// Will become its own Namepsace
void GameSession::SaveGame()
{}
