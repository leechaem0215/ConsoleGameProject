#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>

class HazardSpawner : public Craft::Actor
{
	TYPE_DECLARATIONS(HazardSpawner, Actor)

public:
	HazardSpawner();

private:
	virtual void Tick(float deltaTime) override;

	void SpawnObstacle();
	//void SpawnRandomHazard();

private:
	// 타이머
	Timer timer;
};


