#include "HazardSpawner.h"

#include <Util/Util.h>
#include <Actor/Hazard/Obstacle.h>
#include <Actor/Hazard/Hazard.h>
#include <Actor/Hazard/Enemy.h>
#include <Actor/Platform.h>
#include <Level/Level.h>
#include <Engine/Engine.h>
#include <Util/ResourceManager.h>

using namespace Craft;

HazardSpawner::HazardSpawner(const HazardResources& resources)
    : resources(resources)
{
    groundY = Engine::Get().GetHeight() - 3;

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
    spawnTimer = static_cast<float>(
        Util::RandomRange(15, 30)
        ) / 10.0f;
}

const std::wstring& HazardSpawner::SelectRandomKey(const std::vector<std::wstring>& keys) const
{
    const int index = Util::RandomRange(
        0,
        static_cast<int>(keys.size()) - 1
    );

    return keys[index];
}

void HazardSpawner::SpawnRandomHazard()
{
    const std::shared_ptr<Level> owner = GetOwner();

    if (owner == nullptr)
    {
        return;
    }

    std::vector<int> availableTypes;

    // 0은 아무것도 없는 휴식 구간
    availableTypes.push_back(0);

    if (!resources.obstacleKeys.empty())
    {
        availableTypes.push_back(1);
    }

    if (!resources.enemyKeys.empty())
    {
        availableTypes.push_back(2);
    }

    if (!resources.ceilingKeys.empty())
    {
        availableTypes.push_back(3);
    }

    const int index = Util::RandomRange(
        0,
        static_cast<int>(availableTypes.size()) - 1
    );

    const int selectedType = availableTypes[index];
    const int spawnX = Engine::Get().GetWidth();

    switch (selectedType)
    {
    case 0:
        break;

    case 1:
        owner->SpawnActor<Hazard>(
            SelectRandomKey(resources.obstacleKeys),
            Vector2(spawnX, groundY - 2),
            HazardType::Obstacle
        );
        break;

    case 2:
        owner->SpawnActor<Enemy>(
            SelectRandomKey(resources.enemyKeys),
            groundY - 2
        );
        break;

    case 3:
        owner->SpawnActor<Hazard> (
            SelectRandomKey(resources.ceilingKeys),
            Vector2(spawnX, ceilingY),
            HazardType::Ceiling
        );
        break;
    }
}