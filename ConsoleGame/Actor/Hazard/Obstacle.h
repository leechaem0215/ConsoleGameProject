#pragma once

#include <Actor/Actor.h>

class Obstacle : public Craft::Actor
{
	TYPE_DECLARATIONS(Obstacle, Actor)

public:
	Obstacle(const Craft::Vector2& position,float moveSpeed);

private:
	virtual void Tick(float deltaTime) override;

private:
	float xPosition = 0.0f;
	float moveSpeed = 15.0f;
};