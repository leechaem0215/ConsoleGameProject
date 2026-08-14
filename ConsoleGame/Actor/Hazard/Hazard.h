#pragma once

#include <Actor/Actor.h>
#include <memory>
#include <string>

enum class HazardType
{
    Obstacle,
    Enemy,
    Ceiling
};

class Hazard : public Craft::Actor
{
    TYPE_DECLARATIONS(Hazard, Actor)

public:
    Hazard(const std::wstring& imageKey,int groundY, HazardType type);

    virtual ~Hazard() = default;

    virtual void OnCollision( const std::shared_ptr<Craft::Actor>& other) override;
    void MarkHitPlayer();
private:
    virtual void Tick(float deltaTime) override;

private:
    HazardType type;
    float xPosition = 0.0f;
    float moveSpeed = 20.0f;
    bool hasDamagedPlayer = false;

    bool hasHitPlayer = false;
    bool hasGivenScore = false;
protected:
    int collisionWidthPadding = 2;
    void AddAvoidScore();

public:
    int GetCollisionLeft() const;
    int GetCollisionRight() const;
};