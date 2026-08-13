#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>
#include <Util/ResourceManager.h>

class Player : public Craft::Actor
{
	TYPE_DECLARATIONS(Player, Actor)

public:
	Player(const std::vector<std::wstring>& playerKeys);
	~Player() = default;

public:
	float GetVerticalVelocity() const
	{
		return yVelocity;
	}

	int GetPreviousBottom() const
	{
		return previousPosition.y + GetHeight();
	}

	void LandOn(int platformTop);

	void TakeDamage(int damage);
	int GetHp() const;
	int GetMaxHp() const;

private:
	virtual void Tick(float deltaTime) override;

	// 이동 처리 함수.
	void Move(float direction, float deltaTime);
	void Jump();
	void UpdateJump(float deltaTime);

	void UpdateMoveAnimation(
		float deltaTime,
		float direction
	);

	void ChangePlayerFrame(int frameIndex);
	float previousMoveDirection = 0.0f;

	void StartCrouch();
	void EndCrouch();

	void Fire();
private:
	std::vector<std::wstring> playerKeys;

	bool isCrouching = false;
	int currentMoveFrame = 0;
	int hp = 3;
	int maxHp = 3;

	float moveAnimationTimer = 0.0f;
	float moveAnimationInterval = 0.15f;

	bool wasMovingHorizontally = false;


	float xPosition = 0.0f;
	float yPosition = 0.0f;

	// 플레이어의 바닥(접지) Y 좌표
	float groundY = 0.0f;

	float moveSpeed = 20.0f;

	// 점프 관련 변수
	/* Y축 속도 + 중력 + 착지 판정 */
	float yVelocity = 0.0f;
	float jumpPower = 25.0f;
	float gravity = 100.0f;
	bool isJumping = false;
	
	float fireInterval = 0.2f;
	Timer timer;
};

