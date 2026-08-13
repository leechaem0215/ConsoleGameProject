#pragma once

namespace GameLayout
{
    // 위쪽 게임 영역이 전체 높이에서 차지하는 비율
    constexpr float PlayAreaRatio = 0.8f;

    // 게임 영역과 UI 영역 사이의 구분선 Y 좌표
    inline int GetDividerY(int screenHeight)
    {
        return static_cast<int>(screenHeight * PlayAreaRatio);
    }

    // 플레이어와 장애물이 닿는 게임 영역 바닥
    inline int GetGroundY(int screenHeight)
    {
        return GetDividerY(screenHeight);
    }

    // UI가 시작되는 첫 번째 빈 줄
    inline int GetUIStartY(int screenHeight)
    {
        return GetDividerY(screenHeight) + 1;
    }
}