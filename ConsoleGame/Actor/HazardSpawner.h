#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>

#include <string>
#include <vector>

using namespace Craft;

class HazardSpawner : public Craft::Actor
{
	TYPE_DECLARATIONS(HazardSpawner, Actor)

public:
	explicit HazardSpawner(
		const std::vector<std::wstring>& obstacleKeys
	);

	virtual ~HazardSpawner() = default;

	virtual void Tick(float deltaTime) override;

private:
	void SpawnObstacle();

private:
	std::vector<std::wstring> obstacleKeys;

	Timer timer;
};