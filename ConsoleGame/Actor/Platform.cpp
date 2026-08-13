#include "Platform.h"

#include "Actor/Player/Player.h"

using namespace Craft;

Platform::Platform(
    const Vector2& position,
    int width
)
    : Actor(
        std::wstring(width, L'#'),
        position,
        Color::Green
    ),
    xPosition(static_cast<float>(position.x))
{
    sortingOrder = 4;
}

void Platform::Tick(float deltaTime)
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

void Platform::OnCollision(
    const std::shared_ptr<Actor>& other
)
{
    std::shared_ptr<Player> player =
        std::dynamic_pointer_cast<Player>(other);

    if (player == nullptr)
    {
        return;
    }

    // 위로 올라가는 중이면 착지하지 않음
    if (player->GetVerticalVelocity() < 0.0f)
    {
        return;
    }

    const int platformTop = GetPosition().y;
    const int previousBottom = player->GetPreviousBottom();

    // 이전 프레임부터 이미 발판 아래쪽이었다면 착지하지 않음
    if (previousBottom > platformTop)
    {
        return;
    }

    player->LandOn(platformTop);
}
