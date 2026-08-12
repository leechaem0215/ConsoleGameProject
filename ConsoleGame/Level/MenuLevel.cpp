#include "MenuLevel.h"
#include <Engine/Engine.h>
#include <Game/Game.h>
#include <Input/Input.h>
#include <Render/Renderer.h>
#include <cassert>

using namespace Craft;
MenuLevel::MenuLevel()
{
	// 메뉴 아이템 생성
	itemList.emplace_back(
		std::make_unique<MenuItem>(
			L"Resume Game",
			[]() // 람다
			{
				// 메뉴 토글 함수 호출
				// 토글함수는 게임에서 제공, 전역적으로 접근가능한건 엔진까지 구함
				// 게임 참조로 형변환하고
				Game& game = dynamic_cast<Game&>(Engine::Get());
				game.ToggleMenu();
			}
		)
	);

	itemList.emplace_back(
		std::make_unique<MenuItem>(
			L"Quit Game",
			[]() // 람다
			{
				// 게임 종료 호출
				Engine::Get().Quit();
			}
		)
	);
}

void MenuLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);

	// 입력처리 기반으로 메뉴 아이템 선택여부 보여줄거임
	// 입력 처리 (위/아래 방향키, 엔터, ESC 키)
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game& game = dynamic_cast<Game&>(Engine::Get());
		game.ToggleMenu();

		// 인덱스 초기화
		currentIndex = 0;
	}

	// 위 아래 방향키로 메뉴 오가게 만들거임
	// 배열의 요소 개수 확인
	const int length = static_cast<int>(itemList.size());
	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		// 인덱스 돌리기 (+방향)
		currentIndex = (currentIndex + 1) % length;
	}

	// 엔터 입력 처리 -> 현재 선택된 메뉴의 로직 실행
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// 어써트 추가
		assert(currentIndex >= 0 && currentIndex < (int)itemList.size() && itemList[currentIndex]->onSelected);

		// 메뉴 아이템에 저장된 로직 실행
		itemList[currentIndex]->onSelected();
	}
}

void MenuLevel::Draw()
{ // 그리기
	// 제목 그리기
	Renderer::Get().Submit(L"RUN", Vector2::Zero);

	// 메뉴 아이템 그리기
	const int count = static_cast<int>(itemList.size());
	for (int ix = 0; ix < count; ++ix) {
		// 선택/미선택된 아이템 색상 처리
		Color textColor = (ix == currentIndex) ? selectedColor : unselectedColor; // 선택된 인덱스와 같으면 선택된 색상 지정

		// 아이템 그리기
		Renderer::Get().Submit(
			itemList[ix]->text,
			Vector2(0, 2 + ix),
			textColor
		);
	}
}
