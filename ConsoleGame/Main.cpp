#include <Engine/Engine.h>
#include <Level/GameLevel.h>
#include <Util/ResourceManager.h>
#include <vector>
#include <string>

using namespace Craft;

int main() {
	// 창 제목 설정
	SetConsoleTitleA("RUN Game");

	const std::vector<std::wstring> mapKeys =
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

	const std::vector<std::wstring> obstacleKeys =
		ResourceManager::LoadAll({
			{
				L"Obstacle",
				L"../Assets/Sprites/Obstacle.txt"
			},
			{
				L"Obstacle2",
				L"../Assets/Sprites/Obstacle2.txt"
			}
			});

	const std::vector<std::wstring> enemyKeys =
		ResourceManager::LoadAll({
			{
				L"Enemy",
				L"../Assets/Sprites/Enemy.txt"
			},
			{
				L"Enemy2",
				L"../Assets/Sprites/Enemy2.txt"
			}
			});

	const std::vector<std::wstring> playerKeys =
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
		}
	});

	Craft::Engine engine;

	// 엔진이 사용할 GameLevel을 생성하면서
	// 리소스 키 목록도 함께 전달
	engine.AddNewLevel<GameLevel>(
		mapKeys,
		obstacleKeys,
		enemyKeys,
		playerKeys
	);

	engine.Run();
}