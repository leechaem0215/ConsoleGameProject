#include <Engine/Engine.h>
#include <Level/GameLevel.h>

int main() {
	// 창 제목 설정
	SetConsoleTitleA("RUN Game");

	Craft::Engine engine;
	engine.AddNewLevel<GameLevel>();
	engine.Run();
}