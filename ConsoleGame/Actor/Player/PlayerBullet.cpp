#include "PlayerBullet.h"

using namespace Craft;
PlayerBullet::PlayerBullet(const Vector2& position)
	:Actor(L"o", position, Color::Yellow), //position 전달받은 위치값 사용
	xPosition(static_cast<float>(position.x)) // 멤버변수 초기화 까지 개준거임
{
	sortingOrder = 20;
}

void PlayerBullet::Tick(float deltaTime)
 {
	// 상위 틱 로직 호출
	super::Tick(deltaTime); // Actor라 비어있긴함

	xPosition += moveSpeed * deltaTime;

	// 위치 값 설정 및 갱신
	Vector2 newPosition = GetPosition();
	newPosition.x = static_cast<int>(xPosition);
	SetPosition(newPosition);
}
