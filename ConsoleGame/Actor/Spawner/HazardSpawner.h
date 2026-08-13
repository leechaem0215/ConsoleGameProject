#pragma once

#include <Actor/Actor.h>
#include <Resource/GameResources.h>

class HazardSpawner : public Craft::Actor
{
    TYPE_DECLARATIONS(HazardSpawner, Actor)

public:
    HazardSpawner(const HazardResources& resources);
    virtual ~HazardSpawner() = default;

private:
    virtual void Tick(float deltaTime) override;

    void SpawnRandomHazard();
    void ResetSpawnTimer();

    const std::wstring& SelectRandomKey(
        const std::vector<std::wstring>& keys
    ) const;

private:
    HazardResources resources;

    float spawnTimer = 0.0f;

    int groundY = 0;
    int ceilingY = 2;
};