#include "PlayerBullet.h"

using namespace Craft;
PlayerBullet::PlayerBullet(const Vector2& position)
	:Actor(L"-", position, Color::Blue), //position 전달받은 위치값 사용
	xPosition(static_cast<float>(position.x)) // 멤버변수 초기화 까지 개준거임
{
}

void PlayerBullet::Tick(float deltaTime)
{
	// 상위 틱 로직 호출
	super::Tick(deltaTime); // Actor라 비어있긴함

	// .아래에서 위로 이동처리
	xPosition -= moveSpeed * deltaTime;

	// 화면 벗어나면 안되니까 좌표 검사
	if (xPosition < 0.0f)
	{
		// 삭제 처리
		Destroy();
		return;
	}

	// 위치 값 설정 및 갱신
	Vector2 newPosition = GetPosition();
	newPosition.x = static_cast<int>(xPosition);
	SetPosition(newPosition);
}
