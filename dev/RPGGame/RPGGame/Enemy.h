#pragma once
#include "Character.h"
#include "Player.h"
#include <vector>

class Enemy : public Character
{
public:

    Enemy() = default;

    void PrintStats() const override;
    void TakeTurn(Player& player);

private:

};

