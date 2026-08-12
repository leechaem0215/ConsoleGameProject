#include "Obstacle.h"

using namespace Craft;
Obstacle::Obstacle(const std::wstring& image, float moveSpeed)
	:Actor(image)
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
