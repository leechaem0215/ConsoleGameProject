#include "Enemy.h"
#include <Util/Util.h>// 랜덤 얻어옴
#include <Engine/Engine.h>
#include <Level/Level.h>
#include <Actor/Player/PlayerBullet.h>
#include <Util/ResourceManager.h>
#include <Actor/Player/Player.h>
#include <Level/GameLevel.h>
#include <Util/TextCollision.h>

using namespace Craft;
Enemy::Enemy(const std::wstring& imageKey, int groundY)
	:Actor(ResourceManager::GetText(imageKey),Vector2::Zero,Color::Red)
{
	const int spawnX = Engine::Get().GetWidth() + 2;
	int spawnY = groundY - GetHeight();

	// 위치 설정
	SetPosition(Vector2(spawnX, spawnY));
	xPosition = static_cast<float>(spawnX);
	sortingOrder = 10;
}

void Enemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	const std::shared_ptr<GameLevel> gameLevel = std::dynamic_pointer_cast<GameLevel>(GetOwner());
	const float speedMultiplier = gameLevel ? gameLevel->GetHazardSpeedMultiplier() : 1.0f;
	xPosition -= moveSpeed * speedMultiplier * deltaTime;

	SetPosition(Vector2(
		static_cast<int>(xPosition),
		GetPosition().y
	));

	if (xPosition + GetWidth() < 0.0f)
	{
		Destroy();
	}

	// 여기까지 화면 밖으로 벗어나지 않았다는거
	SetPosition(Vector2(static_cast<int>(xPosition), GetPosition().y));
	// 발사 (탄약 필요)
	// 발사처리는 타이머 기반
	// 타이머 시간 업데이트
	timer.Tick(deltaTime);
	if (!timer.IsTimeOut())
	{
		return;
	}
	// 발사 가능하다면 타이머 리셋
	timer.Reset();
}

void Enemy::OnCollision(const std::shared_ptr<Craft::Actor>& other)
{
	super::OnCollision(other);

	// 충돌한 다른 액터가 플레이어 탄약이면 삭제
	// 커스텀 타입 활용
	if (other && other->IsTypeOf<PlayerBullet>())
	{
		other->Destroy();
		TakeDamage(1);
		return;
	}

	const std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(other);
	if (player
		&& !hasDamagedPlayer
		&& TextCollision::HasVisibleOverlap(*this, *player))
	{
		player->TakeDamage(1);
		hasDamagedPlayer = true;
	}
}

void Enemy::TakeDamage(int damage)
{
	if (hp <= 0)
	{
		return;
	}

	hp -= damage;

	if (hp > 0)
	{
		return;
	}

	if (!hasGivenKillScore)
	{
		const std::shared_ptr<GameLevel> gameLevel =
			std::dynamic_pointer_cast<GameLevel>(
				GetOwner()
			);

		if (gameLevel)
		{
			gameLevel->AddScore(100);
		}

		hasGivenKillScore = true;
	}

	Destroy();
}
