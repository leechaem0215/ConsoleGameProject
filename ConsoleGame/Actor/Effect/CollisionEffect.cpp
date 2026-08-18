#include "CollisionEffect.h"

#include <Util/ResourceManager.h>

#include <stdexcept>

using namespace Craft;

CollisionEffect::CollisionEffect(
    const Vector2& position,
    const std::vector<std::wstring>& keys
)
    : Actor(
        ResourceManager::GetText(keys[0]),
        position,
        Color::Blue
    ),
    effectKeys(keys)
{
    sortingOrder = 20;
}

void CollisionEffect::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    if (effectKeys.empty())
    {
        Destroy();
        return;
    }

    frameTimer += deltaTime;

    if (frameTimer < frameInterval)
    {
        return;
    }

    frameTimer -= frameInterval;
    ++currentFrame;

    // 마지막 프레임까지 재생했으면 이펙트 제거
    if (currentFrame >= static_cast<int>(effectKeys.size()))
    {
        Destroy();
        return;
    }

    ChangeEffectFrame();
}

void CollisionEffect::ChangeEffectFrame()
{
    const std::wstring& selectedKey =
        effectKeys[currentFrame];

    const std::wstring& selectedImage =
        ResourceManager::GetText(selectedKey);

    ChangeImage(selectedImage);
}
