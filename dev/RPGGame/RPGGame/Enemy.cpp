#include "Enemy.h"
#include "Player.h"

void Enemy::PrintStats() const
{

}

void Enemy::TakeTurn(Player& player)
{
	if (RollToHit(&player))
	{
		int healthBefore = player.charStats.Health;

		Attack(this, &player, charStats.Attack);

		// Count the damage actually taken (health can't go below 0)
		player.playerLeaderboard.TotalDamageTaken += healthBefore - player.charStats.Health;
	}
	else
	{
		GEngine->Print("::" + charStats.Name + " misses you! ::", Color::Gray, 1);
	}
}
