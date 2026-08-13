#include "GameLevel.h"
#include <Actor/Player/Player.h>
#include <Actor/Player/PlayerHealth.h>
#include <Render/Renderer.h>
#include <Engine/Engine.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <cassert>
#include <Actor/Background.h>
#include <Actor/Boundary.h>
#include <Actor/Hazard/Obstacle.h>
#include <Actor/Spawner/HazardSpawner.h>
#include <cstdlib>
#include <ctime>


using namespace Craft;

GameLevel::GameLevel(const GameResources& resources)
	: resources(resources)
{
}
void GameLevel::OnInitialized()
{
	Level::OnInitialized();

	// 난수 시드 초기화
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	SpawnActor<Boundary>(
		Vector2(5, 5),
		Engine::Get().GetWidth(),
		Engine::Get().GetHeight()
	);

	SpawnActor<Background>(resources.mapKeys);

	SpawnActor<HazardSpawner>(resources.hazard);

	std::shared_ptr<Player> player =SpawnActor<Player>(resources.playerKeys);

	SpawnActor<PlayerHealth>(player);
}

void GameLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);
	obstacleTimer += deltaTime;

	if (obstacleTimer >= nextObstacleTime)
	{
		SpawnRandomObstacle();
		ResetObstacleTimer();
	}
}

void GameLevel::SpawnRandomObstacle()
{
	Craft::Engine& engine = Craft::Engine::Get();
	int screenW = engine.GetWidth();
	int screenH = engine.GetHeight();

	if (screenH <= 0) return;

	// 장애물은 지면(ground) 높이에만 생성 (Player와 동일한 ground 레벨)
	int groundY = screenH - 5;

	Craft::Vector2 pos(static_cast<int>(screenW), groundY);

	// 속도 약간 랜덤화 (10 ~ 25)
	float speed = 10.0f + static_cast<float>(std::rand() % 16);

	//SpawnActor<Obstacle>(pos, speed);
	SpawnActor<HazardSpawner>(resources.hazard);
}

void GameLevel::ResetObstacleTimer()
{
	obstacleTimer = 0.0f;
	float t = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
	nextObstacleTime = minSpawnTime + t * (maxSpawnTime - minSpawnTime);
}
