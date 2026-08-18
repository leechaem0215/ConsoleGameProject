#pragma once

#include <Actor/Actor.h>

class HeartItem : public Craft::Actor
{
	TYPE_DECLARATIONS(HeartItem, Actor)

public:
	explicit HeartItem(int groundY);
	virtual ~HeartItem() = default;

private:
	virtual void Tick(float deltaTime) override;
	virtual void OnCollision(const std::shared_ptr<Craft::Actor>& other) override;

private:
	float xPosition = 0.0f;
	float moveSpeed = 15.0f;
	bool hasCollected = false;
};
