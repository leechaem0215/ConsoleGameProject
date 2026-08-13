#pragma once

#include <Actor/Actor.h>

class Player;

class PlayerHealth : public Craft::Actor
{
	TYPE_DECLARATIONS(PlayerHealth, Actor)

public:
	PlayerHealth(const std::shared_ptr<Player>& player);
	virtual ~PlayerHealth() = default;

private:
	virtual void Tick(float deltaTime) override;
	void UpdateHeartImage();

private:
	std::weak_ptr<Player> player;
	int previousHp = -1;
};

