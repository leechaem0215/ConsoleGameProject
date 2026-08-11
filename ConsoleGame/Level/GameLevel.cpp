#include "GameLevel.h"
#include <Actor/Player.h>
#include <Render/Renderer.h>
#include <Engine/Engine.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <cassert>
#include <Actor/Background.h>
#include <Actor/Obstacle.h>
#include <cstdlib>
#include <ctime>

void GameLevel::OnInitialized()
{
	Level::OnInitialized();

	SpawnActor<Background>();

	// 난수 시드 초기화
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	SpawnActor<Player>();
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

	SpawnActor<Obstacle>(pos, speed);
}

void GameLevel::ResetObstacleTimer()
{
	obstacleTimer = 0.0f;
	float t = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
	nextObstacleTime = minSpawnTime + t * (maxSpawnTime - minSpawnTime);
}
