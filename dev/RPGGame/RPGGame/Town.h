#pragma once
#include <string>
#include <vector>

class GameSession;
class Player;

class Town
{
public:
	Town(GameSession& _session, Player& player);

	void TownArea();

private:
	void LongRest(Player& player);
	void PlayerLeaderboard(Player& player);

	void PrintMenu() const;

	GameSession& session;
	Player& player;

	std::vector<std::string> townNames = 
	{
	"Puddleby-on-the-Muck",
	"Lesser Snoringham",
	"Goblin's Regret",
	"Upper Wobbleton",
	"Nether Soggington",
	"Bogwater Bottom",
	"Mildly Haunted Hollow",
	"Grumbleshire",
	"Little Stabbing",
	"Sheepish Crossing",
	"Duckwhistle",
	"Cabbage Ridge",
	"Wetsock Valley",
	"Snorebury",
	"Dragon's Leftovers",
	"Fort Probably",
	"Muddlecombe",
	"Tax Collector's End",
	"Questionable Inn Village",
	"Lower Puddingshire",
	"Trollbridge (Toll Applies)",
	"Saint Nobody's Rest",
	"Burnt Bakery",
	"Halfway-to-Somewhere",
	"Bard's Last Gig"
	}; // keep your existing names here

	std::string currentTownName;
	bool bSafeZone = true;
};