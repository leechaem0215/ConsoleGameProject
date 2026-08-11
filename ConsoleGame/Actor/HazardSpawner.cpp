#include "HazardSpawner.h"

#include <Util/Util.h>
#include <Actor/Hazard/Obstacle.h>
#include <Level/Level.h>
#include <Engine/Engine.h>

using namespace Craft;

// 생성할 장애물 이미지 타입 배열
static std::string obstacleType[] =
{
	"###",
	"***",
	"@@@",
	"<-=->",
	")qOp(",
};

HazardSpawner::HazardSpawner()
{
	// 장애물 생성 타이머 설정
	timer.SetTargetTime(Util::RandomRange(0.5f, 0.8f));
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
	// 장애물 생성 처리

	// 장애물 이미지 배열의 길이 확인
	const int length = sizeof(obstacleType) / sizeof(obstacleType[0]);

	// 랜덤 인덱스
	const int index = Util::RandomRange(0, length - 1);
	const int yPosition = Craft::Engine::Get().GetHeight() - 5;

	std::shared_ptr<Level> owner = GetOwner();
	if (owner) // 레벨에 거쳐서 랜덤 생성하고 ..
	{
		owner->SpawnActor<Obstacle>(obstacleType[index], yPosition);
	}
}
