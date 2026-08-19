#pragma once

#include <Actor/Actor.h>

namespace TextCollision
{
    // 텍스트 스프라이트의 공백은 제외하고 실제 문자가 겹치는지 검사한다.
    inline bool HasVisibleOverlap(
        const Craft::Actor& left,
        const Craft::Actor& right
    )
    {
        const Craft::Vector2 leftPosition = left.GetPosition();
        const Craft::Vector2 rightPosition = right.GetPosition();
        const std::wstring& leftImage = left.GetImage();
        const std::wstring& rightImage = right.GetImage();

        int leftX = 0;
        int leftY = 0;

        for (const wchar_t leftCharacter : leftImage)
        {
            if (leftCharacter == L'\r')
            {
                continue;
            }

            if (leftCharacter == L'\n')
            {
                leftX = 0;
                ++leftY;
                continue;
            }

            if (leftCharacter != L' ')
            {
                const int worldX = leftPosition.x + leftX;
                const int worldY = leftPosition.y + leftY;
                int rightX = 0;
                int rightY = 0;

                for (const wchar_t rightCharacter : rightImage)
                {
                    if (rightCharacter == L'\r')
                    {
                        continue;
                    }

                    if (rightCharacter == L'\n')
                    {
                        rightX = 0;
                        ++rightY;
                        continue;
                    }

                    if (rightCharacter != L' '
                        && rightPosition.x + rightX == worldX
                        && rightPosition.y + rightY == worldY)
                    {
                        return true;
                    }

                    ++rightX;
                }
            }

            ++leftX;
        }

        return false;
    }
}
