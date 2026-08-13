#include "Boundary.h"

#include <string>


Boundary::Boundary(const Craft::Vector2& position, int width, int height)
    : Actor(L"", Craft::Vector2::Zero, Craft::Color::White)
{
    std::wstring image;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            const bool isBoundary =
                x == 0 ||
                x == width - 1 ||
                y == 0 ||
                y == height - 1;

            image += isBoundary ? L'#' : L' ';
        }

        if (y < height - 1)
        {
            image += L'\n';
        }
    }

    ChangeImage(image);

    sortingOrder = 1;
    SetPosition(Craft::Vector2(0, 0));
}