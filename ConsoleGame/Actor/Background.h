#pragma once

#include <Actor/Actor.h>
#include <string>
#include <vector>

class Background : public Craft::Actor
{
	TYPE_DECLARATIONS(Background, Actor)

private:
	struct MapPiece
	{
		std::wstring image;

		float xPosition = 0.0f;

		int width = 0;
		int height = 0;
	};


public:
	Background(
		const std::vector<std::wstring>& mapKeys
	);

	virtual ~Background() = default;

private:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

	void AddRandomMap();

private:
	// ResourceManager에서 찾을 맵 키 목록
	std::vector<std::wstring> mapKeys;

	// 현재 화면에 존재하는 맵 조각들
	std::vector<MapPiece> mapPieces;

	float speed = 20.0f;

	int minGap = 3;
	int maxGap = 20;

	int sortingOrder = 2;
};