#pragma once

#include <Actor/Actor.h>

class ScoreUI : public Craft::Actor
{
    TYPE_DECLARATIONS(ScoreUI, Actor)

public:
    ScoreUI();

    virtual ~ScoreUI() = default;

private:
    virtual void Tick(float deltaTime) override;

private:
    int displayedScore = -1;
};