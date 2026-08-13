#pragma once

#include <Level/Level.h>
#include "Resource/GameResources.h"

class GameLevel : public Craft::Level
{
	TYPE_DECLARATIONS(GameLevel, Level)

public:
	GameLevel(const GameResources& resources);
	virtual ~GameLevel() = default;


private:
	virtual void OnInitialized() override;

	void LoadMap(const std::string& filename);
	virtual void Tick(float deltaTime) override;

	void SpawnRandomObstacle();
	void ResetObstacleTimer();

private:
	float obstacleTimer = 0.0f;
	float nextObstacleTime = 2.0f;

	float minSpawnTime = 1.5f;
	float maxSpawnTime = 3.5f;

	GameResources resources;
};

