#include "Obstacle.h"

using namespace Craft;
Obstacle::Obstacle(const Vector2& position, float moveSpeed)
	:Actor("ㅁ", position, Color::BrightWhite), xPosition(position.x), moveSpeed(moveSpeed)
{
	sortingOrder = 10;
}

void Obstacle::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	xPosition -= moveSpeed * deltaTime;

	Vector2 newPosition = GetPosition();
	newPosition.x = static_cast<int>(xPosition);
	SetPosition(newPosition);

	// 화면 밖으로 완전히 나간 경우 제거
	if (newPosition.x + GetWidth() < 0)
	{
		Destroy();
	}
}
