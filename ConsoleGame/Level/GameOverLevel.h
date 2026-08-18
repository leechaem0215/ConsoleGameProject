#pragma once

#include <Level/Level.h>
#include <string>
#include <vector>

class GameOverLevel : public Craft::Level
{
public:
	explicit GameOverLevel(int finalScore);
	virtual ~GameOverLevel() = default;

private:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:
	int finalScore = 0;
	int currentIndex = 0;
	std::vector<std::wstring> items{ L"Retry", L"Quit Game" };
};
