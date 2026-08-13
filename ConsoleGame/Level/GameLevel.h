#pragma once

#include <Level/Level.h>
#include "Resource/GameResources.h"

class GameLevel : public Craft::Level
{
	TYPE_DECLARATIONS(GameLevel, Level)

public:
	GameLevel(const GameResources& resources);
	virtual ~GameLevel() = default;


private:
	virtual void OnInitialized() override;

private:
	GameResources resources;
};

