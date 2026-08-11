#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>

class Player : public Craft::Actor
{
	TYPE_DECLARATIONS(Player, Actor)

public:
	Player();


private:
	virtual void Tick(float deltaTime) override;

	// 이동 처리 함수.
	void Move(float direction, float deltaTime);
	void Jump();
	void UpdateJump(float deltaTime);

private:
	float xPosition = 0.0f;
	float yPosition = 0.0f;

	// 플레이어의 바닥(접지) Y 좌표
	float groundY = 0.0f;

	float moveSpeed = 20.0f;

	// 점프 관련 변수
	/* Y축 속도 + 중력 + 착지 판정 */
	float yVelocity = 0.0f;
	float jumpPower = 25.0f;
	float gravity = 50.0f;
	bool isJumping = false;
	
	
	float fireInterval = 0.2f;
	Timer timer;
};

