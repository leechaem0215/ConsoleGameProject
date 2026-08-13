#pragma once

#include <Actor/Actor.h>

class Player;

class PlayerHealthUI : public Craft::Actor
{
	TYPE_DECLARATIONS(PlayerHealthUI, Actor)

public:
	PlayerHealthUI(const std::shared_ptr<Player>& player);
	virtual ~PlayerHealthUI() = default;

private:
	virtual void Tick(float deltaTime) override;
	void UpdateHeartImage();

private:
	std::weak_ptr<Player> player;
	int previousHp = -1;
};

