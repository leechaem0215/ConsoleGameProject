#pragma once

#include "Actor/Actor.h"

class Boundary : public Craft::Actor
{
    TYPE_DECLARATIONS(Boundary, Actor)
public:
    Boundary(const Craft::Vector2& position, int width, int height);
    virtual ~Boundary() = default;
};