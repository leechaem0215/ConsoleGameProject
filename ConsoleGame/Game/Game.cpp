#include "Game.h"
#include <Level/GameLevel.h>
#include <Level/MenuLevel.h>

// 레벨 2개 추가
Game::Game()
{
	// 두 레벨 생성 및 배열에 추가
	levelList.emplace_back(std::make_shared<GameLevel>()); // 게임레벨이 0번임
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
	int stateIndex = static_cast<int>(state);
	int nextState = 1 - stateIndex; // 인덱스를 1->0, 0->1로 토글하는 공식

	// 레벨 설정 및 상태 값 업데이트
	//mainLevel = levelList[nextState];
	nextLevel = levelList[nextState];
	state = static_cast<State>(nextState);

}
