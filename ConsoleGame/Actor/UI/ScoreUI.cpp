#include "ScoreUI.h"

#include "Level/GameLevel.h"

#include <Level/Level.h>

using namespace Craft;

ScoreUI::ScoreUI()
    : Actor(
        L"SCORE : 0",
        Vector2(2, 1),
        Color::Yellow
    )
{
    sortingOrder = 100;
}

void ScoreUI::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    const std::shared_ptr<GameLevel> gameLevel =
        std::dynamic_pointer_cast<GameLevel>(
            GetOwner()
        );

    if (!gameLevel)
    {
        return;
    }

    const int currentScore =
        gameLevel->GetScore();

    // 점수가 변경되었을 때만 이미지 갱신
    if (displayedScore == currentScore)
    {
        return;
    }

    displayedScore = currentScore;

    const std::wstring scoreText =
        L"SCORE : "
        + std::to_wstring(displayedScore);

    ChangeImage(scoreText);
}