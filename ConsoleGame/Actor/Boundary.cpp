#include "Boundary.h"
#include "Level/GameLayout.h"
#include <string>

Boundary::Boundary(const Craft::Vector2& position, int width, int height)
    : Actor(L"", position, Craft::Color::White)
{
    std::wstring image;

    const int dividerY = GameLayout::GetDividerY(height);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            const bool isOuterBoundary = x == 0 ||  x == width - 1 || y == 0 || y == height - 1;

            const bool isDivider = y == dividerY;

            if (isOuterBoundary || isDivider)
            {
                image += L'#';
            }
            else
            {
                image += L' ';
            }
        }

        if (y < height - 1)
        {
            image += L'\n';
        }
    }

    ChangeImage(image);

    sortingOrder = 1;
}