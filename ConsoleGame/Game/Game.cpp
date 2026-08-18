#include "Game.h"
#include <Level/GameLevel.h>
#include <Level/MenuLevel.h>
#include <Level/GameOverLevel.h>
#include <Util/ResourceManager.h>
#include <Resource/GameResources.h>

using namespace Craft;

// 레벨 2개 추가
Game::Game()
{

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


	// 두 레벨 생성 및 배열에 추가
	levelList.emplace_back(std::make_shared<GameLevel>(resources)); // 게임레벨이 0번임
	levelList.emplace_back(std::make_shared<MenuLevel>());

	// 시작 상태 설정
	state = State::GamePlay;

	// 게임 시작시 활성화할 레벨 설정
	mainLevel = levelList[(int)state];
	// 열거형을 썼기때문에 int로 바꿔서함


}

// 어떤게 활성화 되어있는지에 따라 다른 처리
void Game::ToggleMenu()
{
	if (state == State::GameOver)
	{
		return;
	}

	int stateIndex = static_cast<int>(state);
	int nextState = 1 - stateIndex; // 인덱스를 1->0, 0->1로 토글하는 공식

	// 레벨 설정 및 상태 값 업데이트
	//mainLevel = levelList[nextState];
	nextLevel = levelList[nextState];
	state = static_cast<State>(nextState);

}

void Game::ShowGameOver(int finalScore)
{
	nextLevel = std::make_shared<GameOverLevel>(finalScore);
	state = State::GameOver;
}

void Game::RestartGame()
{
	std::shared_ptr<GameLevel> newGameLevel = std::make_shared<GameLevel>(resources);
	levelList[static_cast<int>(State::GamePlay)] = newGameLevel;
	nextLevel = newGameLevel;
	state = State::GamePlay;
}
