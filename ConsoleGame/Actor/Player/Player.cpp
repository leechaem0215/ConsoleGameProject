#include "Player.h"
#include "Level/GameLayout.h"
#include <Level/Level.h>
#include <Engine/Engine.h>
#include <Input/Input.h>
#include <Actor/Player/PlayerBullet.h> 
#include <Actor/Effect/CollisionEffect.h>
#include <Actor/Hazard/Hazard.h>
#include <Game/Game.h>
#include <Level/GameLevel.h>
#include <Util/TextCollision.h>

using namespace Craft;
Player::Player(const std::vector<std::wstring>& playerKeys,
	const std::vector<std::wstring>& effectKeys)
	: Actor(ResourceManager::GetText(L"Player"),Vector2::Zero,Color::Yellow),
	playerKeys(playerKeys),
	effectKeys(effectKeys)
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
		Game& game = dynamic_cast<Game&>(Engine::Get());
		game.ToggleMenu();
		return;
	}
	timer.Tick(deltaTime);

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
	if (Input::Get().GetKey(VK_SPACE) && timer.IsTimeOut())
	{
		Fire();
		timer.Reset();
	}

	if (isInvincible)
	{
		invincibleTimer += deltaTime;
		blinkTimer += deltaTime;

		// 일정 간격마다 표시 상태 전환
		if (blinkTimer >= blinkInterval)
		{
			blinkTimer = 0.0f;
			SetVisible(!isVisible);
		}

		// 무적 시간 종료
		if (invincibleTimer >= invincibleDuration)
		{
			isInvincible = false;

			invincibleTimer = 0.0f;
			blinkTimer = 0.0f;

			// 안 보이는 상태로 끝나지 않도록 복구
			isVisible = true;
			SetVisible(true);
		}
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
	// 엎드리면 점프 불가
	if (isCrouching)
	{
		return;
	}

	// 이미 두 번 점프했다면 추가 점프 불가
	if (jumpCount >= maxJumpCount)
	{
		return;
	}

	++jumpCount;
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
	isJumping = true;
	// 중력으로 인해 아래쪽 속도가 계속 증가
	yVelocity += gravity * deltaTime;
	// y에 적용
	yPosition += yVelocity * deltaTime;

	// 바닥에 도착하거나 바닥을 통과했을 경우
	if (yPosition >= groundY)
	{
		yPosition = groundY;
		yVelocity = 0.0f;
		isJumping = false;
		jumpCount = 0;
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
	if (isJumping || isCrouching)
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
	if (isJumping || isCrouching)
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

bool Player::TakeDamage(int damage)
{
	// 이미 무적 상태라면 데미지를 받지 않음
	if (isInvincible || damage <= 0 || hp <= 0)
	{
		return false;
	}

	// 최초 피격 시에만 플레이어를 왼쪽으로 짧게 밀어낸다.
	xPosition = (std::max)(
		0.0f,
		xPosition - static_cast<float>(damageKnockbackDistance)
	);

	Vector2 knockbackPosition = GetPosition();
	knockbackPosition.x = static_cast<int>(xPosition);
	SetPosition(knockbackPosition);

	hp -= damage;

	if (hp < 0)
	{
		hp = 0;
	}

	// 피격 직후 무적 상태 시작
	isInvincible = true;

	invincibleTimer = 0.0f;
	blinkTimer = 0.0f;

	

	SetVisible(true);
	if (hp <= 0)
	{
		int finalScore = 0;
		const std::shared_ptr<GameLevel> gameLevel =
			std::dynamic_pointer_cast<GameLevel>(GetOwner());
		if (gameLevel)
		{
			finalScore = gameLevel->GetScore();
		}

		Game& game = dynamic_cast<Game&>(Engine::Get());
		game.ShowGameOver(finalScore);
	}

	return true;
}

int Player::GetHp() const
{
	return hp;
}

void Player::Heal(int amount)
{
	if (amount <= 0 || hp <= 0)
	{
		return;
	}

	hp = (std::min)(maxHp, hp + amount);
}

int Player::GetMaxHp() const
{
	return maxHp;
}


void Player::Fire()
 {
	Vector2 bulletPosition(GetPosition().x + GetWidth(), GetPosition().y + (GetHeight() / 2));

	// 탄약 생성
	std::shared_ptr<Level> owner = GetOwner();
	if (owner) {
		owner->SpawnActor<PlayerBullet>(bulletPosition);
	}
}

void Player::LandOn(int platformTop)
{
	const float landingY =static_cast<float>(platformTop - GetHeight());

	yPosition = landingY;

	Vector2 position = GetPosition();
	position.y = static_cast<int>(landingY);

	SetPosition(position);

	yVelocity = 0.0f;
	isJumping = false;
	jumpCount = 0;
}

void Player::OnCollision(const std::shared_ptr<Actor>& other)
{
	super::OnCollision(other);

	if (!other)
	{
		return;
	}

	std::shared_ptr<Hazard> hazard = std::dynamic_pointer_cast<Hazard>(other);

	if (!hazard)
	{
		return;
	}

	if (!TextCollision::HasVisibleOverlap(*this, *hazard))
	{
		return;
	}

	// 충돌한 장애물은 점수X
	hazard->MarkHitPlayer();

	// 충돌 시 위치를 강제로 변경하지 않고 현재 위치에서 피격 처리한다.
	Vector2 playerPosition = GetPosition();

	// 무적 중이면 데미지와 이펙트 생략
	if (isInvincible)
	{
		return;
	}
	TakeDamage(1);

	// 충돌 이펙트 생성
	std::shared_ptr<Level> owner = GetOwner();

	if (owner && !effectKeys.empty())
	{
		const Vector2 effectPosition(
			playerPosition.x + GetWidth() - 2,
			playerPosition.y + GetHeight() / 2
		);

		owner->SpawnActor<CollisionEffect>(effectPosition,effectKeys);
	}
}
