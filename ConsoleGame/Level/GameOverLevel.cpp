#include "GameOverLevel.h"

#include <Engine/Engine.h>
#include <Game/Game.h>
#include <Input/Input.h>
#include <Render/Renderer.h>

using namespace Craft;

GameOverLevel::GameOverLevel(int finalScore)
	: finalScore(finalScore)
{
}

void GameOverLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);

	const int itemCount = static_cast<int>(items.size());
	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + itemCount) % itemCount;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % itemCount;
	}

	if (!Input::Get().GetKeyDown(VK_RETURN))
	{
		return;
	}

	if (currentIndex == 0)
	{
		dynamic_cast<Game&>(Engine::Get()).RestartGame();
	}
	else
	{
		Engine::Get().Quit();
	}
}

void GameOverLevel::Draw()
{
	const int centerX = Engine::Get().GetWidth() / 2;
	const int centerY = Engine::Get().GetHeight() / 2;

	Renderer::Get().Submit(L"GAME OVER", Vector2(centerX - 5, centerY - 3), Color::Red);
	Renderer::Get().Submit(
		L"SCORE : " + std::to_wstring(finalScore),
		Vector2(centerX - 5, centerY - 1),
		Color::Yellow
	);

	for (int index = 0; index < static_cast<int>(items.size()); ++index)
	{
		const std::wstring prefix = index == currentIndex ? L"> " : L"  ";
		const Color color = index == currentIndex ? Color::Green : Color::White;
		Renderer::Get().Submit(prefix + items[index], Vector2(centerX - 5, centerY + 1 + index), color);
	}
}
