#pragma once

#include <Level/Level.h>

class GameLevel : public Craft::Level
{
	TYPE_DECLARATIONS(GameLevel, Level)

public:
	GameLevel(
		const std::vector<std::wstring>& mapKeys,
		const std::vector<std::wstring>& obstacleKeys,
		const std::vector<std::wstring>& enemyKeys,
		const std::vector<std::wstring>& playerKeys
	);

	virtual ~GameLevel() = default;

private:
	std::vector<std::wstring> mapKeys;
	std::vector<std::wstring> obstacleKeys;
	std::vector<std::wstring> enemyKeys;
	std::vector<std::wstring> playerKeys;
	
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
};

