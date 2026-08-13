#include "Hazard.h"
#include "Actor/Player/Player.h"
#include <Util/ResourceManager.h>

using namespace Craft;
Hazard::Hazard(const std::wstring& imageKey, const Craft::Vector2& position, HazardType type)
    : Actor(
        ResourceManager::GetText(imageKey),
        position,
        Color::Red
    ),
    type(type),
    xPosition(static_cast<float>(position.x))
{
    sortingOrder = 5;
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
