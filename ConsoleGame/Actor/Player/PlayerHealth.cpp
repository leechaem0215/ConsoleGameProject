#include "PlayerHealth.h"
#include <Actor/Player/Player.h>

#include <string>

using namespace Craft;

PlayerHealth::PlayerHealth(const std::shared_ptr<Player>& player)
	:Actor(L"", Vector2(7,6), Color::Red),
	player(player)
{
	sortingOrder = 100;
	UpdateHeartImage();
}

void PlayerHealth::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    std::shared_ptr<Player> currentPlayer =
        player.lock();

    if (currentPlayer == nullptr)
    {
        return;
    }

    if (previousHp == currentPlayer->GetHp())
    {
        return;
    }

    UpdateHeartImage();
}

void PlayerHealth::UpdateHeartImage()
{
    std::shared_ptr<Player> currentPlayer =
        player.lock();

    if (currentPlayer == nullptr)
    {
        return;
    }

    const int hp = currentPlayer->GetHp();
    const int maxHp = currentPlayer->GetMaxHp();

    std::wstring heartImage;

    for (int index = 0; index < maxHp; ++index)
    {
        if (index < hp)
        {
            heartImage += L"♥";
        }
        else
        {
            heartImage += L"♡";
        }

        if (index < maxHp - 1)
        {
            heartImage += L" ";
        }
    }

    ChangeImage(heartImage);

    previousHp = hp;
}
