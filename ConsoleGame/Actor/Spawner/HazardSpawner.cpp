#include "HazardSpawner.h"
#include "Level/GameLayout.h"
#include "Level/GameLevel.h"
#include <Util/Util.h>
#include <Actor/Hazard/Hazard.h>
#include <Actor/Hazard/Enemy.h>
#include <Actor/Item/HeartItem.h>
#include <Level/Level.h>
#include <Engine/Engine.h>

using namespace Craft;

HazardSpawner::HazardSpawner(const HazardResources& resources)
    : resources(resources)
{
    const int screenHeight = Engine::Get().GetHeight();
    groundY = GameLayout::GetDividerY(screenHeight);

    ResetSpawnTimer();
}

void HazardSpawner::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    spawnTimer -= deltaTime;

    if (spawnTimer > 0.0f)
    {
        return;
    }

    SpawnRandomHazard();
    ResetSpawnTimer();
}

void HazardSpawner::ResetSpawnTimer()
{
    const std::shared_ptr<GameLevel> gameLevel =
        std::dynamic_pointer_cast<GameLevel>(
            GetOwner()
        );

    int difficultyLevel = 0;

    if (gameLevel)
    {
        difficultyLevel =
            gameLevel->GetDifficultyLevel();
    }

    // 기본 1.5초에서 난이도마다 0.1초 감소
    const int minimumDelay =
        (std::max)(
            6,
            15 - difficultyLevel
            );

    // 기본 3초에서 난이도마다 0.2초 감소
    const int maximumDelay =
        (std::max)(
            10,
            30 - difficultyLevel * 2
            );

    spawnTimer =
        static_cast<float>(
            Util::RandomRange(
                minimumDelay,
                maximumDelay
            )
            ) / 10.0f;
}

const std::wstring& HazardSpawner::SelectRandomKey(const std::vector<std::wstring>& keys) const
{
    const int index = Util::RandomRange(0,  static_cast<int>(keys.size() - 1));

    return keys[index];
}

void HazardSpawner::SpawnRandomHazard()
{
    const std::shared_ptr<Level> owner = GetOwner();

    if (owner == nullptr)
    {
        return;
    }

    // 약 10% 확률로 회복 아이템을 생성한다.
    const int roll = Util::RandomRange(0, 9);
    if (roll == 0)
    {
        owner->SpawnActor<HeartItem>(groundY);
        return;
    }

    const int index = Util::RandomRange(0, 2);

    switch (index)
    {
    case 0:
        owner->SpawnActor<Hazard>(
            SelectRandomKey(resources.obstacleKeys),
            groundY,
            HazardType::Obstacle
        );
        break;

    case 1:
        owner->SpawnActor<Enemy>(
            SelectRandomKey(resources.enemyKeys),
            groundY
        );
        break;

    case 2:
        owner->SpawnActor<Hazard> (
            SelectRandomKey(resources.ceilingKeys),
            ceilingY,
            HazardType::Ceiling
        );
        break;
    }
}
