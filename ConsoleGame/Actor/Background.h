#pragma once

#include <Actor/Actor.h>
#include <vector>
#include <string>

class Background : public Craft::Actor
{
	TYPE_DECLARATIONS(Background, Actor)
public:
	Background();

private:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:
	std::vector<std::string> lines;
	float scroll = 0.0f; // scroll offset in characters
	float speed = 30.0f; // chars per second (빠름)
};
