#include "GameLevel.h"

#include <Actor/Background.h>
#include <Actor/Boundary.h>
#include <Actor/Player/Player.h>
#include <Actor/UI/PlayerHealthUI.h>
#include <Actor/Spawner/HazardSpawner.h>
#include <Engine/Engine.h>

#include <cstdlib>
#include <ctime>
#include <memory>

using namespace Craft;

GameLevel::GameLevel(const GameResources& resources)
	: resources(resources)
{
}
void GameLevel::OnInitialized()
{
	Level::OnInitialized();

	// 난수 시드 초기화
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	SpawnActor<Boundary>(Vector2::Zero,Engine::Get().GetWidth(),Engine::Get().GetHeight());

	SpawnActor<Background>(resources.mapKeys);

	SpawnActor<HazardSpawner>(resources.hazard);

	std::shared_ptr<Player> player = SpawnActor<Player>(resources.playerKeys);

	SpawnActor<PlayerHealthUI>(player);
}
