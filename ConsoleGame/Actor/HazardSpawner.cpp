#include "HazardSpawner.h"

#include <Util/Util.h>
#include <Actor/Hazard/Obstacle.h>
#include <Level/Level.h>
#include <Engine/Engine.h>
#include <Util/ResourceManager.h>

using namespace Craft;

HazardSpawner::HazardSpawner(
	const std::vector<std::wstring>& obstacleKeys)
	: obstacleKeys(obstacleKeys)
{
	timer.SetTargetTime(
		Util::RandomRange(0.5f, 0.8f)
	);
}

void HazardSpawner::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 시간 경과 처리해야함
	// 타이머 업데이트
	timer.Tick(deltaTime);

	if (!timer.IsTimeOut())
	{
		return;
	}

	// 타이머 초기화
	timer.Reset();

	// 장애물 생성
	SpawnObstacle();
}

void HazardSpawner::SpawnObstacle()
{
	if (obstacleKeys.empty())
	{
		return;
	}

	const int randomIndex =
		Util::RandomRange(
			0,
			static_cast<int>(obstacleKeys.size()) - 1
		);

	const std::wstring& selectedKey =
		obstacleKeys[randomIndex];

	const std::wstring& selectedImage =
		ResourceManager::GetText(selectedKey);

	const int yPosition =
		Engine::Get().GetHeight() - 5;

	std::shared_ptr<Level> owner = GetOwner();

	if (owner)
	{
		owner->SpawnActor<Obstacle>(
			selectedImage,
			yPosition
		);
	}
}