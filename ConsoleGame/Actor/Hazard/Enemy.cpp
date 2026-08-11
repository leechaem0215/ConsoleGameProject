#include "Enemy.h"
#include <Util/Util.h>// 랜덤 얻어옴
#include <Engine/Engine.h>
#include <Level/Level.h>
#include <Actor/PlayerBullet.h>
#include <Actor/DestroyEffect.h>

using namespace Craft;
Enemy::Enemy(const std::string& image, int yPosition)
	:Actor(image)
{
	direction = MoveDirection::Left;
	xPosition = static_cast<float>(Engine::Get().GetWidth() - width - 1);

	// 위치 설정
	SetPosition(Vector2(static_cast<int>(xPosition), yPosition));
}

void Enemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 이동
	float dir = direction == MoveDirection::Left ? -1.0f : 1.0f;
	xPosition += dir * moveSpeed * deltaTime;

	// 화면에 벗어나면 안됌 -> 좌표검사
	if (xPosition + width < 0) // 위치기준 오른쪽, 완전히 벗어나면 
	{
		Destroy(); // 왼쪽으로 벗어나는 경우
		return;
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

void Enemy::OnCollision(const std::shared_ptr<Actor>& other) // other 가 플레이어 탄약이면 사라지도록 할것임
{
	super::OnCollision(other);

	// 충돌한 다른 액터가 플레이어 탄약이면 삭제
	// 커스텀 타입 활용
	if (other->IsTypeOf<PlayerBullet>()) // 매크로가 잘 지정되어 있어야함.
	{
		// 플레이어 탄약 제거
		other->Destroy();

		// 적 액터 제거
		Destroy();

		// 적 파괴 이펙트 생성
		if (GetOwner())
		{
			GetOwner()->SpawnActor<DestroyEffect>(GetPosition());
		}
	}
}
