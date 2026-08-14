#pragma once

#include <Actor/Actor.h>

#include <string>
#include <vector>

class CollisionEffect : public Craft::Actor
{
    TYPE_DECLARATIONS(CollisionEffect, Actor)

public:
    CollisionEffect(
        const Craft::Vector2& position,
        const std::vector<std::wstring>& keys
    );

    virtual ~CollisionEffect() = default;

private:
    virtual void Tick(float deltaTime) override;

    void ChangeEffectFrame();

private:
    std::vector<std::wstring> effectKeys;

    int currentFrame = 0;

    float frameTimer = 0.0f;
    float frameInterval = 0.06f;
};