#pragma once

#include <Actor/Actor.h>
#include <memory>

class Platform : public Craft::Actor
{
    TYPE_DECLARATIONS(Platform, Actor)

public:
    Platform(
        const Craft::Vector2& position,
        int width
    );

    virtual ~Platform() = default;

    virtual void OnCollision(
        const std::shared_ptr<Craft::Actor>& other
    ) override;

private:
    virtual void Tick(float deltaTime) override;

private:
    float xPosition = 0.0f;
    float moveSpeed = 20.0f;
};