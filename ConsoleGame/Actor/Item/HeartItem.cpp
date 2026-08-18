#include "HeartItem.h"

#include <Actor/Player/Player.h>
#include <Engine/Engine.h>
#include <Level/GameLevel.h>

using namespace Craft;

HeartItem::HeartItem(int groundY)
	: Actor(L"\x2665", Vector2::Zero, Color::Green)
{
	const int spawnX = Engine::Get().GetWidth() + 2;
	const int spawnY = groundY - GetHeight() - 2;
	SetPosition(Vector2(spawnX, spawnY));
	xPosition = static_cast<float>(spawnX);
	sortingOrder = 15;
}

void HeartItem::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	float speedMultiplier = 1.0f;
	const std::shared_ptr<GameLevel> gameLevel =
		std::dynamic_pointer_cast<GameLevel>(GetOwner());
	if (gameLevel)
	{
		speedMultiplier = gameLevel->GetHazardSpeedMultiplier();
	}

	xPosition -= moveSpeed * speedMultiplier * deltaTime;
	SetPosition(Vector2(static_cast<int>(xPosition), GetPosition().y));

	if (xPosition + GetWidth() < 0.0f)
	{
		Destroy();
	}
}

void HeartItem::OnCollision(const std::shared_ptr<Actor>& other)
{
	if (hasCollected)
	{
		return;
	}

	const std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(other);
	if (!player || player->GetHp() >= player->GetMaxHp())
	{
		return;
	}

	hasCollected = true;
	player->Heal(1);
	Destroy();
}
