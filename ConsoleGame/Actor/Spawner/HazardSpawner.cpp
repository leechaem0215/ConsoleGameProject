#include "HazardSpawner.h"
#include "Level/GameLayout.h"
#include <Util/Util.h>
#include <Actor/Hazard/Hazard.h>
#include <Actor/Hazard/Enemy.h>
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
    spawnTimer = static_cast<float>(Util::RandomRange(15, 30)) / 10.0f;
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

    const int index = Util::RandomRange(0, 5);
    const int spawnX = Engine::Get().GetWidth() + 2;

    switch (index)
    {
    case 0:
        break;

    case 1:
        owner->SpawnActor<Hazard>(
            SelectRandomKey(resources.obstacleKeys),
            groundY,
            HazardType::Obstacle
        );
        break;

    case 2:
        owner->SpawnActor<Enemy>(
            SelectRandomKey(resources.enemyKeys),
            groundY
        );
        break;

    case 3:
        owner->SpawnActor<Hazard> (
            SelectRandomKey(resources.ceilingKeys),
            ceilingY,
            HazardType::Ceiling
        );
        break;
    }
}