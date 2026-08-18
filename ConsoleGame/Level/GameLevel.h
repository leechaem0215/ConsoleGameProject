#pragma once

#include <Level/Level.h>
#include "Resource/GameResources.h"

class GameLevel : public Craft::Level
{
	TYPE_DECLARATIONS(GameLevel, Level)

public:
	GameLevel(const GameResources& resources);
	virtual ~GameLevel() = default;

	void AddScore(int amount);
	int GetScore() const;
	int GetDifficultyLevel() const;
	float GetHazardSpeedMultiplier() const;

private:
	virtual void OnInitialized() override;
	virtual void Tick(float deltaTime) override;

private:
	GameResources resources;

	int score = 0;
	int scorePerSecond = 10;
	float scoreTimer = 0.0f;
};

