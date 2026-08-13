#include "Player.h"
#include "Level/GameLayout.h"
#include <Engine/Engine.h>
#include <Input/Input.h>
#include <Actor/Player/PlayerBullet.h> 

using namespace Craft;
Player::Player(const std::vector<std::wstring>& playerKeys)
	: Actor(ResourceManager::GetText(L"Player"),Vector2::Zero,Color::Yellow),
	playerKeys(playerKeys)
{
	ChangePlayerFrame(0);

	const int screenWidth = Engine::Get().GetWidth();
	const int screenHeight = Engine::Get().GetHeight();

	const int x = (screenWidth - GetWidth()) / 2;
	const int y = GameLayout::GetDividerY(screenHeight) - GetHeight();

	SetPosition(Vector2(x, y));

	xPosition = static_cast<float>(x);
	yPosition = static_cast<float>(y);

	groundY = static_cast<float>(y);

	timer.SetTargetTime(fireInterval);

	sortingOrder = 10;
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	previousPosition = GetPosition();


	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		QuitGame();
	}

	// 아래 방향키를 누르는 동안 엎드림
	if (Input::Get().GetKey(VK_DOWN))
	{
		StartCrouch();
	}
	else
	{
		EndCrouch();
	}

	float direction = 0.0f;

	if (!isCrouching)
	{
		if (Input::Get().GetKey(VK_RIGHT))
		{
			direction = 1.0f;
		}

		if (Input::Get().GetKey(VK_LEFT))
		{
			direction = -1.0f;
		}

		if (Input::Get().GetKeyDown(VK_UP))
		{
			Jump();
		}
	}

	Move(direction, deltaTime);
	UpdateJump(deltaTime);

	UpdateMoveAnimation(
		deltaTime,
		direction
	);

	// 탄약 발사 로직
	if (Input::Get().GetKeyDown(VK_SPACE))
	{
		Fire();
	}
}

void Player::Move(float direction, float deltaTime) // Tick에서 호출할거임
{
	xPosition += direction * moveSpeed * deltaTime;

	const int screenWidth = Engine::Get().GetWidth();
	const int playerWidth = GetWidth();

	const int maximumX =
		(std::max)(0, screenWidth - playerWidth);

	if (xPosition < 0)
	{
		xPosition = 0.0f;
	}

	if (xPosition >= screenWidth)
	{
		xPosition = static_cast<float>(Engine::Get().GetWidth() - playerWidth);
	}

	Vector2 newPosition = GetPosition();
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
	ChangePlayerFrame(5);
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

void Player::UpdateMoveAnimation(
	float deltaTime,
	float direction)
{
	// 점프 중에는 PlayerJ 이미지 유지
	if (isJumping)
	{
		return;
	}
	if (!isCrouching)
	{
		return;
	}

	// 좌우 키를 누르지 않은 경우
	if (direction == 0.0f)
	{
		if (currentMoveFrame != 0)
		{
			ChangePlayerFrame(0);
		}

		moveAnimationTimer = 0.0f;
		previousMoveDirection = 0.0f;

		return;
	}

	// 이동을 막 시작했거나 방향을 바꾼 경우
	if (previousMoveDirection != direction)
	{
		moveAnimationTimer = 0.0f;
		previousMoveDirection = direction;

		if (direction > 0.0f)
		{
			// 오른쪽 걷기 첫 프레임
			ChangePlayerFrame(1);
		}
		else
		{
			// 왼쪽 걷기 첫 프레임
			ChangePlayerFrame(3);
		}

		return;
	}

	moveAnimationTimer += deltaTime;

	if (moveAnimationTimer < moveAnimationInterval)
	{
		return;
	}

	moveAnimationTimer -= moveAnimationInterval;

	if (direction > 0.0f)
	{
		// 오른쪽: 1 ↔ 2
		const int nextFrame =
			(currentMoveFrame == 1) ? 2 : 1;

		ChangePlayerFrame(nextFrame);
	}
	else
	{
		// 왼쪽: 3 ↔ 4
		const int nextFrame =
			(currentMoveFrame == 3) ? 4 : 3;

		ChangePlayerFrame(nextFrame);
	}
}

void Player::ChangePlayerFrame(int frameIndex)
{
	if (frameIndex < 0 ||
		frameIndex >= static_cast<int>(playerKeys.size()))
	{
		return;
	}

	const std::wstring& selectedKey =playerKeys[frameIndex];

	const std::wstring& selectedImage = ResourceManager::GetText(selectedKey);

	ChangeImage(selectedImage);

	currentMoveFrame = frameIndex;
}

void Player::StartCrouch()
{
	// 점프 중에는 엎드리지 않음
	if (isJumping)
	{
		return;
	}

	// 이미 엎드린 상태면 다시 처리하지 않음
	if (isCrouching)
	{
		return;
	}

	isCrouching = true;

	ChangePlayerFrame(6);

	// 이미지 높이가 바뀌었으므로
	// 발이 기존 바닥에 맞도록 위치를 다시 계산
	const int dividerY =GameLayout::GetDividerY(Engine::Get().GetHeight());

	const int crouchY = dividerY - GetHeight();

	yPosition = static_cast<float>(crouchY);

	Vector2 position = GetPosition();

	position.y = crouchY;

	SetPosition(position);
}

void Player::EndCrouch()
{
	if (!isCrouching)
	{
		return;
	}

	isCrouching = false;

	// 기본 서 있는 이미지로 복귀
	ChangePlayerFrame(0);

	const int dividerY =GameLayout::GetDividerY(Engine::Get().GetHeight());

	const int standingY = dividerY - GetHeight();

	yPosition = static_cast<float>(standingY);

	groundY = static_cast<float>(standingY);

	Vector2 position = GetPosition();

	position.y = standingY;

	SetPosition(position);
}

void Player::TakeDamage(int damage)
{
	hp -= damage;

	if (hp <= 0)
	{
		QuitGame();
	}
}

int Player::GetHp() const
{
	return hp;
}

int Player::GetMaxHp() const
{
	return maxHp;
}


void Player::Fire()
{
	// 탄약 생성 위치 구하기
	// 플레이어의 가운데 위치
	// <=A=>   < 위치 x에서 2칸 이동하면 A 위치가 됨.
	//   ^   탄약이 제대로 가리키려면 해당 위치여야한다.
	Vector2 bulletPosition(GetPosition().x + (GetWidth() / 2), GetPosition().y);

	// 탄약 생성
	std::shared_ptr<Level> owner = GetOwner();
	if (owner) {
		//owner->SpawnActor<PlayerBullet>(bulletPosition);
	}
}
void Player::LandOn(int platformTop)
{
	Vector2 position = GetPosition();

	position.y = platformTop - GetHeight();

	SetPosition(position);

	yVelocity = 0.0f;
	isJumping = false;
}