#include "GameLevel.h"

#include <Actor/Background.h>
#include <Actor/Boundary.h>
#include <Actor/Player/Player.h>
#include <Actor/UI/PlayerHealthUI.h>
#include <Actor/UI/ScoreUI.h>
#include <Actor/Spawner/HazardSpawner.h>
#include <Engine/Engine.h>

#include <cstdlib>
#include <ctime>
#include <memory>

using namespace Craft;

GameLevel::GameLevel(const GameResources& resources)
	: resources(resources)
{
}

void GameLevel::AddScore(int amount)
{
    if (amount <= 0)
    {
        return;
    }

    score += amount;
}

int GameLevel::GetScore() const
{
    return score;
}

int GameLevel::GetDifficultyLevel() const
{
    return score / 500;
}

float GameLevel::GetHazardSpeedMultiplier() const
{
    const float multiplier =
        1.0f
        + static_cast<float>(
            GetDifficultyLevel()
            ) * 0.1f;

    return (std::min)(multiplier, 2.0f);
}

void GameLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);
	scoreTimer += deltaTime;
	while (scoreTimer >= 1.0f)
	{
		scoreTimer -= 1.0f;
		AddScore(scorePerSecond);
	}
}

void GameLevel::OnInitialized()
{
	Level::OnInitialized();

	// 난수 시드 초기화
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	SpawnActor<Boundary>(Vector2::Zero,Engine::Get().GetWidth(),Engine::Get().GetHeight());

	//SpawnActor<Background>(resources.mapKeys);

	SpawnActor<HazardSpawner>(resources.hazard);

	std::shared_ptr<Player> player = SpawnActor<Player>(resources.playerKeys, resources.effectKeys);

	SpawnActor<PlayerHealthUI>(player);
	SpawnActor<ScoreUI>();
}
