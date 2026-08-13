#include <Engine/Engine.h>
#include <Level/GameLevel.h>
#include <Util/ResourceManager.h>
#include <Resource/GameResources.h>
#include <vector>
#include <string>

using namespace Craft;

int main() {
	// 창 제목 설정
	SetConsoleTitleA("RUN Game");
	GameResources resources;

	resources.mapKeys =
		ResourceManager::LoadAll({
			{
				L"Map",
				L"../Assets/Maps/Map.txt"
			},
			{
				L"Map2",
				L"../Assets/Maps/Map2.txt"
			},
			{
				L"Map3",
				L"../Assets/Maps/Map3.txt"
			},
			{
				L"Map4",
				L"../Assets/Maps/Map4.txt"
			}
			});

	resources.hazard.obstacleKeys =
		ResourceManager::LoadAll({
			{
				L"Obstacle",
				L"../Assets/Sprites/Obstacle.txt"
			},
			{
				L"Obstacle2",
				L"../Assets/Sprites/Obstacle2.txt"
			},
			{
				L"Obstacle3",
				L"../Assets/Sprites/Obstacle3.txt"
			}
			});

	resources.hazard.ceilingKeys =
		ResourceManager::LoadAll({
			{
				L"Ceiling_G1",
				L"../Assets/Sprites/Ceiling_G1.txt"
			},
			{
				L"Ceiling_G2",
				L"../Assets/Sprites/Ceiling_G2.txt"
			},
			{
				L"Ceiling_G3",
				L"../Assets/Sprites/Ceiling_G3.txt"
			}
			});

	resources.hazard.enemyKeys =
		ResourceManager::LoadAll({
			{
				L"Enemy_S1",
				L"../Assets/Sprites/Enemy_S1.txt"
			},
			{
				L"Enemy_S2",
				L"../Assets/Sprites/Enemy_S2.txt"
			},
			{
				L"Enemy_U1",
				L"../Assets/Sprites/Enemy_U1.txt"
			},
			{
				L"Enemy_U2",
				L"../Assets/Sprites/Enemy_U2.txt"
			}
			});

	resources.playerKeys =
	ResourceManager::LoadAll({
		{
			L"Player",
			L"../Assets/Sprites/Player.txt"
		},
		{
			L"PlayerR1",
			L"../Assets/Sprites/PlayerR1.txt"
		},
		{
			L"PlayerR2",
			L"../Assets/Sprites/PlayerR2.txt"
		},
		{
			L"PlayerL1",
			L"../Assets/Sprites/PlayerL1.txt"
		},
		{
			L"PlayerL2",
			L"../Assets/Sprites/PlayerL2.txt"
		},
		{
			L"PlayerJ",
			L"../Assets/Sprites/PlayerJ.txt"
		},
		{
			L"PlayerD",
			L"../Assets/Sprites/PlayerD.txt"
		},
	});

	resources.effectKeys =
		ResourceManager::LoadAll({
			{
				L"Effect_t1",
				L"../Assets/Effect/Effect_t1.txt"
			},
			{
				L"Effect_t2",
				L"../Assets/Effect/Effect_t2.txt"
			}
			});

	Craft::Engine engine;

	// 엔진이 사용할 GameLevel을 생성하면서
	// 리소스 키 목록도 함께 전달
	engine.AddNewLevel<GameLevel>(resources);

	engine.Run();
}