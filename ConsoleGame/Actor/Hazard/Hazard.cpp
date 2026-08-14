#include "Hazard.h"
#include "Actor/Player/Player.h"
#include <Util/ResourceManager.h>
#include <Engine/Engine.h>
#include "Level/GameLevel.h"

using namespace Craft;
Hazard::Hazard(const std::wstring& imageKey, int groundY, HazardType type)
    : Actor(ResourceManager::GetText(imageKey),Vector2::Zero, Color::Red),type(type)
{
    const int spawnX = Engine::Get().GetWidth() + 2;
    int spawnY = 0;

    switch (type)
    {
    case HazardType::Obstacle:
        // 이미지 아래쪽이 바닥 구분선에 닿도록 배치
        spawnY = groundY - GetHeight();
        break;

    case HazardType::Ceiling:
        // 화면 위쪽 테두리 바로 아래에 배치
        spawnY = 1;
        break;
    }

    SetPosition( Vector2( spawnX, spawnY));

    xPosition = static_cast<float>(spawnX);
    sortingOrder = 10;
}

void Hazard::OnCollision(const std::shared_ptr<Craft::Actor>& other)
{
    if (hasDamagedPlayer)
    {
        return;
    }

    std::shared_ptr<Player> player =
        std::dynamic_pointer_cast<Player>(other);

    if (player == nullptr)
    {
        return;
    }

    player->TakeDamage(1);
    hasDamagedPlayer = true;
}

void Hazard::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    xPosition -= moveSpeed * deltaTime;

    SetPosition(Vector2(
        static_cast<int>(xPosition),
        GetPosition().y
    ));

    if (xPosition + GetWidth() < 0.0f)
    {
        Destroy();
    }
}

int Hazard::GetCollisionLeft() const
{
    return GetPosition().x - collisionWidthPadding;
}

int Hazard::GetCollisionRight() const
{
    return GetPosition().x
        + GetWidth()
        + collisionWidthPadding;
}

void Hazard::MarkHitPlayer()
{
    hasHitPlayer = true;
}

void Hazard::AddAvoidScore()
{
    if (hasGivenScore)
    {
        return;
    }

    if (hasHitPlayer)
    {
        return;
    }

    // 일반 장애물과 천장 장애물만 회피 점수 지급
    if (type != HazardType::Obstacle &&
        type != HazardType::Ceiling)
    {
        return;
    }

    const std::shared_ptr<GameLevel> gameLevel =
        std::dynamic_pointer_cast<GameLevel>(
            GetOwner()
        );

    if (!gameLevel)
    {
        return;
    }

    hasGivenScore = true;

    gameLevel->AddScore(100);
}