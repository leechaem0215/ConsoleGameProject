#include "Player.h"
#include <Engine/Engine.h>
#include <Input/Input.h>

using namespace Craft;
Player::Player()
	:Actor("⸜(๑'8'๑)⸝", Vector2::Zero, Color::Yellow)
{
	// 생성 위치 설정
	// A 가 화면의 가운데 올 수 있도록 해줌
	int x = -(Engine::Get().GetWidth() / 2);
	int y = (Engine::Get().GetHeight() - 5);
	SetPosition(Vector2(x, y));

	// x위치 저장
	xPosition = static_cast<float>(x);
	// y위치 저장
	yPosition = static_cast<float>(y);

	// groundY 초기화 (이 위치를 바닥으로 사용)
	groundY = static_cast<float>(Engine::Get().GetHeight() - 5);

	// 연사 타이머 시간 설정
	timer.SetTargetTime(fireInterval);
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	if (Input::Get().GetKeyDown(VK_ESCAPE)) {
		QuitGame();
	}
	
	float direction = 0.0f;

	if (Input::Get().GetKey(VK_RIGHT))
	{
		direction = 1.0f;
	}
	if (Input::Get().GetKey(VK_LEFT))
	{
		direction = -1.0f;
	}
	Move(direction, deltaTime);


	if (Input::Get().GetKeyDown(VK_UP))
	{
		Jump();
	}

	UpdateJump(deltaTime);
}

void Player::Move(float direction, float deltaTime) // Tick에서 호출할거임
{
	// x위치 업데이트
	// 이동 처리 -> 이동 방향과 빠르기를 적용해서 새로운 위치를 구하는 것
	// 이동 방향 (direction) / 빠르기(moveSpeed) | 시간
	// 동속도 운동 : 이동 거리 = 기존의 위치 + 이동 방향 x 빠르기 x 시간 : 시간에 따른 이동량
	// 빠르기는 항상 단위가 중요하다.
	xPosition += direction * moveSpeed * deltaTime;

	// 화면 제어
	if (xPosition < 0) {
		xPosition = 0.0f;
	}
	if (xPosition + width >= Engine::Get().GetWidth()) {
		xPosition = static_cast<float>(Engine::Get().GetWidth() - width);
	}

	// 위치 업데이트
	Vector2 newPosition = GetPosition();
	// float 값을 int로 형변환할 때 소수점 값은 버림 처리된다는 점 주의
	// 이거 고려해서 작성하는거
	newPosition.x = static_cast<int>(xPosition);
	SetPosition(newPosition);
}

void Player::Jump()
{
	if (isJumping)
	{
		return;
	}
	isJumping = true;
	yVelocity = -jumpPower;
}

void Player::UpdateJump(float deltaTime)
{
	if (!isJumping)
	{
		return;
	}

	// 중력으로 인해 아래쪽 속도가 계속 증가
	yVelocity += gravity * deltaTime;
	// y에 적용
	yPosition += yVelocity * deltaTime;

	// 바닥 위치: 멤버 groundY 사용
	const float gY = groundY;

	// 바닥에 도착하거나 바닥을 통과했을 경우
	if (yPosition >= gY)
	{
		yPosition = gY;
		yVelocity = 0.0f;
		isJumping = false;
	}

	Vector2 newPosition = GetPosition();
	newPosition.y = static_cast<int>(yPosition);

	SetPosition(newPosition);
}
