#include "PlayerHealthUI.h"
#include "Level/GameLayout.h"
#include <Actor/Player/Player.h>
#include <Engine/Engine.h>
#include <string>

using namespace Craft;

PlayerHealthUI::PlayerHealthUI(const std::shared_ptr<Player>& player)
	:Actor(L"", Vector2::Zero, Color::Red),
	player(player)
{
    const int statusY = GameLayout::GetUIStartY(Engine::Get().GetHeight());
    SetPosition(Vector2(2,statusY));
	sortingOrder = 100;
	UpdateHeartImage();
}

void PlayerHealthUI::Tick(float deltaTime)
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

void PlayerHealthUI::UpdateHeartImage()
{
    std::shared_ptr<Player> currentPlayer = player.lock();

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
