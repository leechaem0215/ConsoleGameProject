#include "Background.h"
#include <Engine/Engine.h>
#include <Render/Renderer.h>
#include <Math/Vector2.h>
#include <Math/Color.h>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>

Background::Background()
{
	// 배경은 가장 뒤에 그려지도록 낮은 정렬값 사용
	// 프레임 초기값이 -1 이므로 이 값보다 작으면 그려지지 않음
	// 따라서 배경은 -1로 설정하여 먼저 그려지도록 함
	sortingOrder = -1;

	// 파일 로드 (레벨에서 사용하는 Map.txt 를 배경으로 사용)
	std::string path = std::string("../Assets/") + "Map.txt";

	FILE* file = nullptr;
	fopen_s(&file, path.c_str(), "rt");
	if (!file) {
		// 실행 폴더에도 시도
		fopen_s(&file, "Map.txt", "rt");
	}

	if (!file) {
		// 파일 없으면 아무것도 하지 않음
		return;
	}

	const int bufferSize = 4096;
	char* buffer = new char[bufferSize] {};
	while (fgets(buffer, bufferSize, file))
	{
		size_t len = strlen(buffer);
		while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
			buffer[--len] = '\0';
		}
		lines.emplace_back(buffer);
	}
	delete[] buffer;
	buffer = nullptr;

	fclose(file);
	file = nullptr;
}

void Background::Tick(float deltaTime)
{
	// 오른쪽 -> 왼쪽으로 이동하려면 scroll 값을 증가시킴
	scroll += speed * deltaTime;
}

void Background::Draw()
{
	if (lines.empty())
	{
		return;
	}

	// 화면 크기
	int screenW = Craft::Engine::Get().GetWidth();
	int screenH = Craft::Engine::Get().GetHeight();

	// 각 라인을 화면에 제출
	const int lineCount = static_cast<int>(lines.size());
	for (int y = 0; y < lineCount && y < screenH; ++y)
	{
		const std::string& src = lines[y];
		if (src.empty())
		{
			Craft::Renderer::Get().Submit(std::string(screenW, ' '), Craft::Vector2(0, y), Craft::Color::Cyan, sortingOrder);
			continue;
		}

		int len = static_cast<int>(src.length());
		if (len == 0)
		{
			continue;
		}

		// 반복 문자열을 만들어 충분히 긴 뷰를 뽑아냄
		std::string extended = src;
		while ((int)extended.length() < screenW + len) extended += src;

		int start = static_cast<int>(floor(scroll)) % len;
		if (start < 0) start += len;

		std::string view = extended.substr(start, screenW);

		Craft::Renderer::Get().Submit(view, Craft::Vector2(0, y), Craft::Color::White, sortingOrder);
	}
}
